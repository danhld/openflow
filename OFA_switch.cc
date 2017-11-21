#include "OFA_switch.h"
//#include "NotifierConsts.h"
#include "openflow.h"
#include "messages/Open_Flow_Message_m.h"
#include "messages/OFP_Packet_In_m.h"
#include "messages/OFP_Packet_Out_m.h"
#include "messages/OFP_Flow_Mod_m.h"
#include "messages/OFP_Features_Reply_m.h"
#include "OF_Wrapper.h"

#include "inet/networklayer/ipv4/IPv4Datagram.h"
#include "inet/networklayer/arp/ipv4/ARPPacket_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"

#define MSGKIND_CONNECT  0
#define MSGKIND_SEND     1
#define MSGKIND_FLOW_ENTRY_TIMER 2



Define_Module(OFA_switch);

OFA_switch::OFA_switch()
{

}

OFA_switch::~OFA_switch()
{

}

void OFA_switch::initialize()
{
    cModule *ITModule = getParentModule()->getSubmodule("buffer");
    buffer = check_and_cast<Buffer *>(ITModule);


    getParentModule()->subscribe("NF_NO_MATCH_FOUND",this);

    cModule *ITModule3 = getParentModule()->getSubmodule("flow_Table");
    flow_table = check_and_cast<Flow_Table *>(ITModule3);


    NF_FLOOD_PACKET = registerSignal("NF_FLOOD_PACKET");
    NF_SEND_PACKET = registerSignal("NF_SEND_PACKET");
    NF_NO_MATCH_FOUND = registerSignal("NF_NO_MATCH_FOUND");

    const char *address = par("address");
    int port = par("port");
    timeout = par("flow_timeout");
    socket.bind(*address ? L3Address(address) : L3Address(), port);


    socket.setOutputGate(gate("tcpOut"));

    socket.setDataTransferMode(TCP_TRANSFER_OBJECT);

    timeoutMsg = new cMessage("timer");

    timeoutMsg->setKind(MSGKIND_CONNECT);
    scheduleAt((simtime_t)par("startTime"), timeoutMsg);
}

void OFA_switch::handleMessage(cMessage *msg)
{

    if (msg->isSelfMessage())
    {
        if (msg->getKind()==MSGKIND_FLOW_ENTRY_TIMER)
        {
            oxm_basic_match *match = (oxm_basic_match *) msg->getContextPointer();
            flow_table->deleteEntry(match);
        }
        else
        {
            handleTimer(msg);
        }
    }
    if (dynamic_cast<Open_Flow_Message *>(msg) != NULL) {
        Open_Flow_Message *of_msg = (Open_Flow_Message *)msg;
        ofp_type type = (ofp_type)of_msg->getHeader().type;
        EV << "OFA_switch, ofp_type: " << type << endl;
        switch (type)
        {
        case OFPT_PACKET_OUT:
            handlePacketOutMessage(of_msg);
            break;
        case OFPT_FLOW_MOD:
            handleFlowModMessage(of_msg);
            break;
        case OFPT_FEATURES_REQUEST:
            handleFeaturesRequestMessage(of_msg);
            break;
        default:
            break;
        }

    }
    delete msg;
}

void OFA_switch::handleTimer(cMessage *msg)
{
    switch (msg->getKind())
    {
    case MSGKIND_CONNECT:
        EV << "starting session\n";
        connect(); // active OPEN

        break;

    case MSGKIND_SEND:
        break;
    }
}

void OFA_switch::handleFeaturesRequestMessage(Open_Flow_Message *of_msg)
{
    OFP_Features_Reply *featuresReply = new OFP_Features_Reply("FeaturesReply");
    featuresReply->getHeader().version = OFP_VERSION;
    featuresReply->getHeader().type = OFPT_FEATURES_REPLY;
    featuresReply->setByteLength(1);
    featuresReply->setKind(TCP_C_SEND);
    int connID = socket.getConnectionId();
    featuresReply->setDatapath_id(connID);
    int capacity = buffer->getCapacity();
    featuresReply->setN_buffers(capacity);
    socket.send(featuresReply);
}

void OFA_switch::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    Enter_Method_Silent();
    //printNotificationBanner(category, details);

    // no matching entry found in flow table
    if (id == NF_NO_MATCH_FOUND)
    {
        handlePacket();
    }
}


// handle unmatched packets and send packet-in message to controller
void OFA_switch::handlePacket()
{
    EthernetIIFrame *frame = buffer->dequeue();
    OFP_Packet_In *packetIn = new OFP_Packet_In("packetIn");
    packetIn->getHeader().version = OFP_VERSION;
    packetIn->getHeader().type = OFPT_PACKET_IN;
    packetIn->setReason(OFPR_NO_MATCH);

    packetIn->setByteLength(1);

    if (par("sendCompletePacket").boolValue()==true || buffer->isfull())
    {
        // send full packet with packet-in message
        packetIn->encapsulate(frame);
        packetIn->setBuffer_id(OFP_NO_BUFFER);
    } else
    {
        // store packet in buffer and only send header fields
        oxm_basic_match *match = new oxm_basic_match();
        match->OFB_IN_PORT = frame->getArrivalGate()->getIndex();

        match->OFB_ETH_SRC = frame->getSrc();
        match->OFB_ETH_DST = frame->getDest();
        match->OFB_ETH_TYPE = frame->getEtherType();
        //extract ARP specific match fields if present
        if(frame->getEtherType()==ETHERTYPE_ARP){
            ARPPacket *arpPacket = check_and_cast<ARPPacket *>(frame->getEncapsulatedPacket());
            match->OFB_ARP_OP = arpPacket->getOpcode();
            match->OFB_ARP_SHA = arpPacket->getSrcMACAddress();
            match->OFB_ARP_THA = arpPacket->getDestMACAddress();
            match->OFB_ARP_SPA = arpPacket->getSrcIPAddress();
            match->OFB_ARP_TPA = arpPacket->getDestIPAddress();
        }

        packetIn->setMatch(*match);
        uint32_t buffer_id = buffer->storeMessage(frame);

        packetIn->setBuffer_id(buffer_id);
    }
    socket.send(packetIn);

}



void OFA_switch::connect()
{
    socket.renewSocket();
    int connectPort = par("connectPort");
    /*
    const char *connectAddress; // = par("connectAddress");

    EV << "connectAddress  = " << connectAddress << " connectPort =" << connectPort << endl;


   // if (getParentModule()->getParentModule()->getSubmodule("controller") != NULL)
    {
        // multiple controllers; full path is needed for connect address
//        connectAddress = (getParentModule()->getParentModule())->getSubmodule("controller")->getFullPath().c_str();
        cModule *ctl = getSystemModule()->getSubmodule("controller");
        if(ctl != NULL) {
            EV << "ctl->getFullPath() = " << ctl->getFullPath().c_str() << endl;
            connectAddress = ctl->getFullPath().c_str();
        }
        EV << "After: connectAddress  = " << connectAddress << endl;
    }
    */

    L3Address ctlIPAddr;
    EV << "connect L3Address  = " << L3AddressResolver().tryResolve("controller", ctlIPAddr) << endl;
//    EV << "result: connectAddress  = " << ctlIPAddr << endl;
//    socket.connect(L3AddressResolver().resolve(connectAddress), connectPort);
    socket.connect(ctlIPAddr, connectPort);

}



void OFA_switch::handlePacketOutMessage(Open_Flow_Message *of_msg)
{
    EV << "OFA_switch::handlePacketOutMessage" << endl;
    OFP_Packet_Out *packet_out_msg = (OFP_Packet_Out *) of_msg;

    uint32_t buffer_id = packet_out_msg->getBuffer_id();
    uint32_t in_port = packet_out_msg->getIn_port();
    unsigned int actions_size = packet_out_msg->getActionsArraySize();
    if (buffer_id != OFP_NO_BUFFER)
    {
        // packet stored in buffer
        for (unsigned int i = 0; i < actions_size; i++)
        {
            ofp_action_header *action = &(packet_out_msg->getActions(i));
            execute_packet_out_action(action, buffer_id, in_port);
        }
    }
    else
    {
        // packet encapsulated in packet-out message
        EthernetIIFrame *frame =  dynamic_cast<EthernetIIFrame *>(packet_out_msg->decapsulate());


        for (unsigned int i = 0; i < actions_size; i++)
        {
            ofp_action_header *action = &(packet_out_msg->getActions(i));
            execute_packet_out_action(action, frame, in_port);
        }
    }
}

// packet stored in buffer
void OFA_switch::execute_packet_out_action(ofp_action_header *action, uint32_t buffer_id, uint32_t inport)
{


    ofp_action_output *action_output = (ofp_action_output *) action;
    if(action_output->port == OFPP_ANY){
        EV << "Dropping packet in buffer with ID: " << buffer_id << endl;
        delete buffer->returnMessage(buffer_id);
        return;
    }
    uint32_t outport = action_output->port;
    OF_Wrapper *wrapper = new OF_Wrapper();
    wrapper->buffer_id = buffer_id;
    if (outport == OFPP_FLOOD)
    {
        emit(NF_FLOOD_PACKET, wrapper);
    }
    else
    {
        wrapper->outport = outport;
        emit(NF_SEND_PACKET, wrapper);
    }

}
// packet encapsulated and not stored in buffer
void OFA_switch::execute_packet_out_action(ofp_action_header *action, EthernetIIFrame *frame, uint32_t inport)
{

    ofp_action_output *action_output = (ofp_action_output *) action;
    EV << "outport: " << action_output->port << endl;
    uint32_t outport = action_output->port;
    OF_Wrapper *wrapper = new OF_Wrapper();
    wrapper->buffer_id = OFP_NO_BUFFER;
    wrapper->setframe(frame);

    if (outport == OFPP_FLOOD)
    {
        EV << "outport==ofpp_flood" << endl;
        emit(NF_FLOOD_PACKET, wrapper);
    }
    else
    {
        wrapper->outport = outport;
        emit(NF_SEND_PACKET, wrapper);
    }
    //    }

}

void OFA_switch::handleFlowModMessage(Open_Flow_Message *of_msg)
{
    EV << "OFA_switch::handleFlowModMessage" << endl;
    OFP_Flow_Mod *flow_mod_msg = (OFP_Flow_Mod *) of_msg;
    oxm_basic_match *match = &flow_mod_msg->getMatch();


    // Construct unique name for flow entry timeout message

    ofp_action_output actions[1];
    actions[0] = flow_mod_msg->getActions(0);
    entry_data *data = new entry_data();
    flow_table_instructions *instruc = new flow_table_instructions;
    instruc->actions[0] = actions[0];
    data->instruc = instruc;
    flow_table->addEntry(match, data);

    oxm_basic_match *copy = new oxm_basic_match();

    copy->OFB_ETH_DST = match->OFB_ETH_DST;
    copy->OFB_ETH_SRC = match->OFB_ETH_SRC;
    copy->OFB_ETH_TYPE = match->OFB_ETH_TYPE;
    copy->OFB_IN_PORT = match->OFB_IN_PORT;
    copy->OFB_IPV4_DST = match->OFB_IPV4_DST;
    copy->wildcards = match->wildcards;

    std::stringstream timerName;
    timerName << "sMac:" << copy->OFB_ETH_SRC;
    timerName << ", dMac:" << copy->OFB_ETH_DST;
    timerName << ", iPort:" << copy->OFB_IN_PORT;
    timerName << ", eType:" << copy->OFB_ETH_TYPE;

    cMessage *timeoutmsg = new cMessage(timerName.str().c_str());
    timeoutmsg->setKind(MSGKIND_FLOW_ENTRY_TIMER);
    timeoutmsg->setContextPointer(copy);
    scheduleAt(simTime()+timeout, timeoutmsg);

}
