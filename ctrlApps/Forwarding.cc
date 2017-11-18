#include <omnetpp.h>
#include "Forwarding.h"

#include "openflow.h"
#include "OF_Wrapper.h"
#include "OFA_controller.h"

#include "messages/Open_Flow_Message_m.h"
#include "messages/OFP_Packet_In_m.h"

#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/ipv4/IPv4InterfaceData.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/linklayer/ethernet/EtherMAC.h"
#include "inet/networklayer/contract/ipv4/IPv4Address.h"
#include "inet/networklayer/ipv4/IPv4Datagram.h"
#include "inet/networklayer/arp/ipv4/ARPPacket_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"

#include <algorithm>

using namespace std;
using namespace inet;


Define_Module(Forwarding);

Forwarding::Forwarding()
{

}

Forwarding::~Forwarding()
{

}

void Forwarding::initialize(int stage)
{
    if(stage==0){
        EV << "Forwarding: Initialize Stage 0" << endl;
        cModule *ITModule = getParentModule()->getSubmodule("ofa_controller");
        controller = check_and_cast<OFA_controller *>(ITModule);

        // RegisterSignal is here only used to get signal ID
        // This module does not emit any events for these signals
        connIDSignal = registerSignal("connID");
        PacketInSignalId = registerSignal("PacketIn");

        // Register to these signals as they are used for communication between ctrlApp and ofa_controller
        // Subscribe one level in hierarchy above because signals are only propagated upwards
        getParentModule()->subscribe(connIDSignal,this);
        getParentModule()->subscribe(PacketInSignalId,this);

        // Does this controller app answer ARP requests?
        isArpOracle = par("isArpOracle").boolValue();

        WATCH_VECTOR(nodeInfo);

    }

    if (stage==4)
    {
        EV << "Forwarding: Initialize Stage 4" << endl;

        extractTopology(topo_forw, nodeInfo);

        assignAddresses(topo_forw, nodeInfo);

    }
}

//bool selectFunction(cModule *mod, void *){
//
//    return strcmp(mod->getNedTypeName(),"openflow.nodes.StandardHostRandom")==0
//            || strcmp(mod->getNedTypeName(),"openflow.nodes.Open_Flow_Switch")==0;
//
//}

bool selectFunctionForwarding(cModule *mod, void *v_ptr){
    int id = *(int *)v_ptr;
    int domainID = -1;

    if(mod->hasPar("doaminID")){
        domainID = mod->par("domainID").longValue();
    }else if(mod->getParentModule()->hasPar("doaminID")){
        domainID = mod->getParentModule()->par("domainID").longValue();
    }

    return (strcmp(mod->getNedTypeName(),"inet.nodes.inet.StandardHost")==0 ||
            strcmp(mod->getNedTypeName(),"openflow.nodes.Open_Flow_Switch")==0) &&
            domainID==id;
}

void  Forwarding::extractTopology(cTopology &topo, NodeInfoVector &nodeInfo)
{

    // We either have knowledge about the entire network or only about our own domain
    if(par("domainID").longValue() >= 0){
        int domainID = getParentModule()->par("domainID").longValue();
        topo.extractFromNetwork(selectFunctionForwarding, (int *) &domainID);
        EV << "cTopology found " << topo.getNumNodes() << " nodes for domain " << domainID << ".\n";
    }else{
        // Use specified ned type to extract relevant nodes
        topo.extractByNedTypeName(cStringTokenizer(par("nedTypes")).asVector());
        EV << "cTopology found " << topo.getNumNodes() << " nodes\n";
    }

    nodeInfo.resize(topo.getNumNodes());
    for (int i= 0; i< topo.getNumNodes(); i++)
    {
        cModule *mod = topo.getNode(i)->getModule();
        nodeInfo[i].isIPNode = L3AddressResolver().findInterfaceTableOf(mod) != NULL;
        nodeInfo[i].isOpenFlow = (mod->findSubmodule("flow_Table")!=-1);
        nodeInfo[i].name = topo.getNode(i)->getModule()->getFullPath();
        if (nodeInfo[i].isIPNode)
        {
            nodeInfo[i].ift = L3AddressResolver().interfaceTableOf(mod);
            nodeInfo[i].rt = L3AddressResolver().routingTableOf(mod);
        }
        if (nodeInfo[i].isOpenFlow)
        {
            EV << "extractTopology: OF-Switch found" << endl;
        }
    }
}

void Forwarding::assignAddresses(cTopology &topo, NodeInfoVector &nodeInfo)
{
    for (int i=0; i<topo.getNumNodes(); i++)
    {
        if (!nodeInfo[i].isIPNode)
            continue;

        inet::IInterfaceTable *ift = nodeInfo[i].ift;
        for (int k=0; k<ift->getNumInterfaces(); k++)
        {
            InterfaceEntry *ie = ift->getInterface(k);
            if (!ie->isLoopback())
            {
                IPv4Address addr = ie->ipv4Data()->getIPAddress();
                nodeInfo[i].address = addr;
                nodeInfo[i].macAddress = ie->getMacAddress();
                break;
            }
        }
    }
}





void Forwarding::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    EV << "Received signal " << getSignalName(id) << " at module " << this->getFullName() << "." << endl;
    if (id == PacketInSignalId)
    {

        if (dynamic_cast<OF_Wrapper *>(obj) != NULL)
        {
            OF_Wrapper *wrapper = (OF_Wrapper *) obj;
            Open_Flow_Message *of_msg = wrapper->msg;
            OFP_Packet_In *packet_in = (OFP_Packet_In *) of_msg;
            uint32_t buffer_id = packet_in->getBuffer_id();

            MACAddress src_mac;
            MACAddress dst_mac;
            IPv4Address dst_ip;
            if (buffer_id == OFP_NO_BUFFER)
            {

                src_mac = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getSrc();
                dst_mac = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getDest();
            } else
            {

                src_mac = packet_in->getMatch().OFB_ETH_SRC;
                dst_mac = packet_in->getMatch().OFB_ETH_DST;
            }
            TCPCommand *ind = dynamic_cast<TCPCommand *>(packet_in->getControlInfo());

            if (!ind)
                error("Switch: no TCPCommand control info in message (not from TCP?)");
            int connID = ind->getConnId();
            EV <<  "connID: " << connID << endl;


            int outputGateId;

            bool routeFound = 0;



            for (int i=0; i<topo_forw.getNumNodes(); i++)
            {
                cTopology::Node *destNode = topo_forw.getNode(i);


                EtherMAC *eth =  (EtherMAC *) destNode->getModule()->getSubmodule("eth", 0)->getSubmodule("mac");
                MACAddress mac = eth->getMACAddress();

                // Skip forwarding for Ethernet frames with braodcast destination address
                if(mac.isBroadcast()){
                    break;
                }

                if (mac == dst_mac)
                {
                    routeFound = 1;
                    std::string destModName = destNode->getModule()->getFullName();

                    topo_forw.calculateUnweightedSingleShortestPathsTo(destNode);

                    cTopology::Node *nextNode = NULL;

                    while (nextNode != destNode) {

                        for (int j=0; j<topo_forw.getNumNodes(); j++)
                        {
                            if (i==j)continue;
                            // Only choose OpenFlow switches, otherwise proceed to next node in for loop
                            if (!nodeInfo[j].isOpenFlow)
                                continue;

                            cTopology::Node *atNode = topo_forw.getNode(j);
                            // Only choose nodes which have shortest path to destination node
                            if (atNode->getNumPaths()==0)
                                continue;

                            // Only proceed if nextNode has not been chosen yet or atNode is equal to nextNode
                            if(nextNode != NULL && atNode != nextNode)
                                continue;

                            // Only proceed if connection id of atNode is equal to connection id of OpenFlow switch which has sent packet-in message
                            // or nextNode has been chosen
                            if(nextNode == NULL && nodeInfo[j].connID!= connID)
                                continue;


                            outputGateId = atNode->getPath(0)->getLocalGate()->getIndex();
                            uint32_t outport = outputGateId;
                            EV << "--------------------------------------";
                            EV << "shortest path for : " << atNode->getModule()->getFullName() << endl;
                            EV << outport << endl;
                            EV << "remote node: "<< atNode->getPath(0)->getRemoteNode()->getModule()->getFullName() << endl;
                            nextNode = atNode->getPath(0)->getRemoteNode();

                            connID_outport.push_back(std::pair<int, uint32_t> (nodeInfo[j].connID, outport));

                        }
                    }
                    typedef UnsortedMap::iterator iter;
                    iter begin(connID_outport.begin());
                    iter end(connID_outport.end());
//                    std::map<int, uint32_t>::reverse_iterator i_first = connID_outport.end();
                    reverse_iterator<iter> rev_end(begin);
                    reverse_iterator<iter> rev_iterator(end);
//                    std::map<int, uint32_t>::reverse_iterator i_last = connID_outport.begin();
                    while (rev_iterator!=rev_end)
                    {
                        oxm_basic_match *match = new oxm_basic_match();
                        if (buffer_id == OFP_NO_BUFFER)
                        {

                            //                            match->OFB_IN_PORT = packet_in->getEncapsulatedPacket()->getArrivalGate()->getIndex();
                            match->OFB_ETH_SRC = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getSrc();
                            match->OFB_ETH_DST = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getDest();
                            match->OFB_ETH_TYPE = dynamic_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket())->getEtherType();
                            match->wildcards = OFPFW_IN_PORT;
                        } else
                        {

                            //                            match->OFB_IN_PORT = packet_in->getMatch().OFB_IN_PORT;
                            match->OFB_ETH_SRC = packet_in->getMatch().OFB_ETH_SRC;
                            match->OFB_ETH_DST = packet_in->getMatch().OFB_ETH_DST;
                            match->OFB_ETH_TYPE = packet_in->getMatch().OFB_ETH_TYPE;
                            match->wildcards = OFPFW_IN_PORT;
                        }
//                        EV << "nodeinfo.connid: " << nodeInfo[j].connID<< "connID: " << connID << endl;
//                        controller->sendFlowModMessage(OFPFC_ADD, match, outport, nodeInfo[j].connID);
//                        if (nodeInfo[j].connID == connID)
//                            controller->sendPacket(buffer_id, packet_in, outport, connID);

                        controller->sendFlowModMessage(OFPFC_ADD, match, rev_iterator->second, rev_iterator->first);
                        if (rev_iterator->first == connID)
                            controller->sendPacket(buffer_id, packet_in, rev_iterator->second, connID);
                        rev_iterator++;
                    }
                    connID_outport.clear();
                }
            }

            if(!routeFound && isArpOracle){
                routeFound = processARPPacket(packet_in, connID);

            }


            if (routeFound == 0)
            {
                controller->floodPacket(buffer_id, packet_in, connID);
            }
        }


    }
    else if (id == connIDSignal)
    {
        if (dynamic_cast<OF_Wrapper *>(obj) != NULL)
        {
            OF_Wrapper *wrapper = (OF_Wrapper *) obj;
            int connID = wrapper->connID;
            IPv4Address *ip_src = wrapper->ip_src;
            for (int i=0; i<topo_forw.getNumNodes(); i++)
            {
                //                cTopology::Node *destNode = topo_forw.getNode(i);
                //                EtherMAC *eth =  (EtherMAC *) destNode->getModule()->getSubmodule("eth", 0)->getSubmodule("mac");
                //                                MACAddress mac = eth->getMACAddress();
                IPv4Address *ip = &nodeInfo[i].address;
                //                    EV << "-----------------------------------------------------------------" << endl;
                //                    EV << *ip << " "<< *ip_src << endl;
                if (*ip == *ip_src)
                {
                    nodeInfo[i].connID = connID;
                }
            }
        }

    }

}

bool Forwarding::processARPPacket(OFP_Packet_In *packet_in, int connID){
    oxm_basic_match *match = new oxm_basic_match();
    ARPPacket *arpPacket;
    EthernetIIFrame *frame;
    if(packet_in->getBuffer_id() == OFP_NO_BUFFER){
        frame = check_and_cast<EthernetIIFrame *>(packet_in->getEncapsulatedPacket());
        if(frame!=NULL){
            match->OFB_IN_PORT = frame->getArrivalGate()->getIndex();
            match->OFB_ETH_SRC = frame->getSrc();
            match->OFB_ETH_DST = frame->getDest();
            match->OFB_ETH_TYPE = frame->getEtherType();
            //extract ARP specific match fields if present
            if(frame->getEtherType()==ETHERTYPE_ARP){
                arpPacket = check_and_cast<ARPPacket *>(frame->getEncapsulatedPacket());
                match->OFB_ARP_OP = arpPacket->getOpcode();
                match->OFB_ARP_SHA = arpPacket->getSrcMACAddress();
                match->OFB_ARP_THA = arpPacket->getDestMACAddress();
                match->OFB_ARP_SPA = arpPacket->getSrcIPAddress();
                match->OFB_ARP_TPA = arpPacket->getDestIPAddress();
            }
        }
    }else{
        match = &packet_in->getMatch();
        arpPacket = new ARPPacket();
        frame = new EthernetIIFrame();
    }

    if(match->OFB_ETH_TYPE != ETHERTYPE_ARP){
        return false;
    }


    EV << "Processing ARP packet:\n";

    // "?Is the opcode ares_op$REQUEST?  (NOW look at the opcode!!)"
    switch (match->OFB_ARP_OP)
    {
        case ARP_REQUEST:
        {
            EV << "Packet was ARP REQUEST, sending REPLY\n";

            arpPacket->setName("arpREPLY");

            MACAddress tha;

            for (unsigned int i=0; i<nodeInfo.size(); i++)
            {
                EV << "Testing " << nodeInfo[i].address << " and " << match->OFB_ARP_TPA << endl;
                if(nodeInfo[i].address == match->OFB_ARP_TPA){
                    tha = nodeInfo[i].macAddress;
                    break;
                }

            }

            if(tha.isUnspecified()){
                EV << "No MAC address found for ARP REQUEST, triggering broadcast\n";
                return false;
            }

            arpPacket->setDestIPAddress(match->OFB_ARP_SPA);
            arpPacket->setDestMACAddress(match->OFB_ARP_SHA);
            arpPacket->setSrcIPAddress(match->OFB_ARP_TPA);
            arpPacket->setSrcMACAddress(tha);
            arpPacket->setOpcode(ARP_REPLY);

            frame->setSrc(tha);
            frame->setDest(match->OFB_ARP_SHA);

            if(packet_in->getBuffer_id() != OFP_NO_BUFFER){
                frame->setEtherType(ETHERTYPE_ARP);
                frame->encapsulate(arpPacket);
                packet_in->encapsulate(frame);
                // Delete buffered ARP REQUEST
                controller->sendPacket(packet_in->getBuffer_id(), packet_in, OFPP_ANY, connID);
            }

            // Trigger sending of ARP REPLY
            controller->sendPacket(OFP_NO_BUFFER, packet_in, match->OFB_IN_PORT, connID);



            return true;
        }
        case ARP_REPLY:
        {
            EV << "Packet was ARP REPLY and will be ignored\n";

            break;
        }
        default:
        {
            error("Unsupported opcode %d in received ARP packet",match->OFB_ARP_OP);
            break;
        }

    }
    return false;

}








