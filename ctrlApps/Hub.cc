#include <omnetpp.h>
#include "Hub.h"
#include "openflow.h"

#include "OF_Wrapper.h"
#include "OFA_controller.h"

#include "messages/Open_Flow_Message_m.h"
#include "messages/OFP_Packet_In_m.h"

Define_Module(Hub);

Hub::Hub()
{

}

Hub::~Hub()
{

}

void Hub::initialize()
{
    cModule *ITModule = getParentModule()->getSubmodule("ofa_controller");
    controller = check_and_cast<OFA_controller *>(ITModule);

    // RegisterSignal is here only used to get signal ID
    // This module does not emit any events for these signals
    // Register to these signals as they are used for communication between ctrlApp and ofa_controller
    // Subscribe one level in hierarchy above because signals are only propagated upwards
    getParentModule()->subscribe("PacketIn",this);

}

// receive Packet-In signal from controller application;
// flood all packets.
void Hub::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    EV << "Hub::receiveSignal" << endl;
//    if(getSignalName(id)!="PacketIn")
//    {
//        EV << "Hub: Signal-Fehler" << endl;
//        return;
//    }
    if (dynamic_cast<OF_Wrapper *>(obj) != NULL)
    {
        OF_Wrapper *wrapper = (OF_Wrapper *) obj;
        Open_Flow_Message *of_msg = wrapper->msg;
        OFP_Packet_In *packet_in = (OFP_Packet_In *) of_msg;
        uint32_t buffer_id = packet_in->getBuffer_id();
        controller->floodPacket(buffer_id, packet_in, 0);
    }

}
