#include <omnetpp.h>
#include "Switch.h"
#include "openflow.h"
#include "OF_Wrapper.h"
#include "OFA_controller.h"

#include "messages/Open_Flow_Message_m.h"
#include "messages/OFP_Packet_In_m.h"

using namespace std;


Define_Module(Switch);

Switch::Switch()
{

}

Switch::~Switch()
{

}

void Switch::initialize()
{
    cModule *ITModule = getParentModule()->getSubmodule("ofa_controller");
    controller = check_and_cast<OFA_controller *>(ITModule);

    // RegisterSignal is here only used to get signal ID
    // This module does not emit any events for these signals
    // Register to these signals as they are used for communication between ctrlApp and ofa_controller
    // Subscribe one level in hierarchy above because signals are only propagated upwards
    getParentModule()->subscribe("PacketIn",this);

}


void Switch::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    if (dynamic_cast<OF_Wrapper *>(obj) != NULL)
    {
        OF_Wrapper *wrapper = (OF_Wrapper *) obj;
        Open_Flow_Message *of_msg = wrapper->msg;
        OFP_Packet_In *packet_in = (OFP_Packet_In *) of_msg;
        uint32_t buffer_id = packet_in->getBuffer_id();


        uint32_t inport;
        MACAddress src_mac;
        MACAddress dst_mac;
        // packet is encapsulated in packet-in message
        if (buffer_id == OFP_NO_BUFFER)
        {
        inport = packet_in->getEncapsulatedPacket()->getArrivalGate()->getIndex();
        src_mac = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getSrc();
        dst_mac = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getDest();
        }
        //packet is stored in buffer
        else
        {
            inport = packet_in->getMatch().OFB_IN_PORT;
            src_mac = packet_in->getMatch().OFB_ETH_SRC;
            dst_mac = packet_in->getMatch().OFB_ETH_DST;
        }
        // get connection ID for OpenFlow switch which has sent the Packet-In message
        TCPCommand *ind = dynamic_cast<TCPCommand *>(packet_in->getControlInfo());

        if (!ind)
            error("Switch: no TCPCommand control info in message (not from TCP?)");
        int connID = ind->getConnId();
        EV <<  "connID: " << connID << endl;
        MAC_connID m_c;
        m_c.address = src_mac;
        m_c.connID = connID;

        //search map for source mac address
        std::multimap<MAC_connID, uint32_t>::iterator i = mac_to_port.begin();
        bool mac_found2 = 0;
        while (i!=mac_to_port.end())
        {

            if (src_mac.compareTo(i->first.address)==0 && connID == i->first.connID )
            {
                mac_found2 = 1;
            }
            i++;
        }
        //insert source address into map
        if (mac_found2==0)
        {

            mac_to_port.insert(pair<MAC_connID, uint32_t> (m_c, inport));
        }


        // search map for destination mac address
        std::multimap<MAC_connID, uint32_t>::iterator j = mac_to_port.begin();
        bool mac_found = 0;
        while (j!=mac_to_port.end())
        {

            if (dst_mac.compareTo(j->first.address)==0 && connID == j->first.connID )
            {
                mac_found = 1;
                EV << "mac-adresse gefunden" << dst_mac <<endl;
                uint32_t outport = j->second;
                EV << outport << endl;
                oxm_basic_match *match = new oxm_basic_match();;
                // packet is encapsulated
                if (buffer_id == OFP_NO_BUFFER)
                {
                match->OFB_IN_PORT = packet_in->getEncapsulatedPacket()->getArrivalGate()->getIndex();
                match->OFB_ETH_SRC = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getSrc();
                match->OFB_ETH_DST = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getDest();
                match->OFB_ETH_TYPE = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getEtherType();
                }
                // packet is stored in buffer
                else
                {
                    match->OFB_IN_PORT = packet_in->getMatch().OFB_IN_PORT;
                    match->OFB_ETH_SRC = packet_in->getMatch().OFB_ETH_SRC;
                    match->OFB_ETH_DST = packet_in->getMatch().OFB_ETH_DST;
                    match->OFB_ETH_TYPE = packet_in->getMatch().OFB_ETH_TYPE;
                }
                controller->sendFlowModMessage(OFPFC_ADD, match, outport, connID);
                controller->sendPacket(buffer_id, packet_in, outport, connID);
            }

            j++;
        }
        if (mac_found==0)
        {
            EV << "mac-adresse nicht gefunden" << endl;
            controller->floodPacket(buffer_id, packet_in, connID);

        }
    }



}
