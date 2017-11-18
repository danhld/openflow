#include "Open_Flow_Processing.h"

using namespace std;


Define_Module(Open_Flow_Processing);

Open_Flow_Processing::Open_Flow_Processing()
{

}

Open_Flow_Processing::~Open_Flow_Processing() {

}
void Open_Flow_Processing::initialize()
 {
    cModule *ITModule = getParentModule()->getSubmodule("flow_Table");
    flow_table = check_and_cast<Flow_Table *>(ITModule);
    cModule *ITModule2 = getParentModule()->getSubmodule("buffer");
    buffer = check_and_cast<Buffer *>(ITModule2);

    NF_NO_MATCH_FOUND = registerSignal("NF_NO_MATCH_FOUND");
    NF_SEND_PACKET = registerSignal("NF_SEND_PACKET");
    NF_FLOOD_PACKET = registerSignal("NF_FLOOD_PACKET");

    getParentModule()->subscribe("NF_SEND_PACKET",this);
    getParentModule()->subscribe("NF_FLOOD_PACKET",this);


    WATCH_VECTOR(port_vector);
    // By default, all ports are enabled
    port_vector.resize(gateSize("ifIn"),1);

    busy = false;
    serviceTime = par("serviceTime");
 }

// invoked by Spanning Tree module;
// disable ports for broadcast packets
void Open_Flow_Processing::disablePorts(vector<int> ports)
{
    EV << "disablePorts method at " << this->getParentModule()->getName() << endl;

    for (unsigned int i = 0; i<ports.size(); i++)
    {
        port_vector[ports[i]] = 0;
    }
    for (unsigned int i = 0; i < port_vector.size(); i++)
    {
        // Highlight links that belong to spanning tree

        if (port_vector[i]==1)
        {
            cGate *gateOut = getParentModule()->gate("ethg$o", i);
            do {
                cDisplayString& connDispStrOut = gateOut->getDisplayString();
                connDispStrOut.parse("ls=green,3,dashed");
                gateOut=gateOut->getNextGate();

            } while (!gateOut->getOwnerModule()->getModuleType()->isSimple());

            cGate *gateIn = getParentModule()->gate("ethg$i", i);
            do {
                cDisplayString& connDispStrIn = gateIn->getDisplayString();
                connDispStrIn.parse("ls=green,3,dashed");
                gateIn=gateIn->getPreviousGate();

            } while (!gateIn->getOwnerModule()->getModuleType()->isSimple());
        }
    }
}

 void Open_Flow_Processing::handleMessage(cMessage *msg)
 {
         // self message to implement service time
         if (msg->isSelfMessage())
         {
             cMessage *data_msg = (cMessage *) msg->getContextPointer();
             delete msg;
             processQueuedMsg(data_msg);
             if (msg_list.empty())
             {
                 busy = false;
             }
             else
             {
                 cMessage *msgfromlist = msg_list.front();
                 msg_list.pop_front();
                 char buf[80];
                 sprintf(buf, " %d pakets in queue", msg_list.size());
                 getParentModule()->getDisplayString().setTagArg("t", 0, buf);
                 std::list<cMessage *>::iterator i = msg_list.begin();
                     while (i!=msg_list.end())
                     {
                         EV << (*i)->getFullPath() << endl;
                         i++;
                     }
                 cMessage *event = new cMessage("event");
                 event->setContextPointer(msgfromlist);
                 scheduleAt(simTime()+serviceTime, event);
             }
         }
         else
         {
             if (busy) {
                 msg_list.push_back(msg);
                 char buf[80];
                 sprintf(buf, " %d pakets in queue", msg_list.size());
                 getParentModule()->getDisplayString().setTagArg("t", 0, buf);
             }
             else
             {

                 busy = true;

                 cMessage *event = new cMessage("event");
                 event->setContextPointer(msg);
                 scheduleAt(simTime()+serviceTime, event);
             }
         }
 }

 void Open_Flow_Processing::processQueuedMsg(cMessage *data_msg)
 {
     if (dynamic_cast<EthernetIIFrame *>(data_msg) != NULL) {
                   frameBeingReceived = (EthernetIIFrame *)data_msg;
                   EV << "Broadcast?: " <<frameBeingReceived->getDest().isBroadcast() << endl;
                   oxm_basic_match *match = new oxm_basic_match();

                   //extract match fields
                   match->OFB_IN_PORT = frameBeingReceived->getArrivalGate()->getIndex();
                   match->OFB_ETH_SRC = frameBeingReceived->getSrc();
                   match->OFB_ETH_DST = frameBeingReceived->getDest();
                   match->OFB_ETH_TYPE = frameBeingReceived->getEtherType();
                   //extract ARP specific match fields if present
                   if(frameBeingReceived->getEtherType()==ETHERTYPE_ARP){
                       ARPPacket *arpPacket = check_and_cast<ARPPacket *>(frameBeingReceived->getEncapsulatedPacket());
                       match->OFB_ARP_OP = arpPacket->getOpcode();
                       match->OFB_ARP_SHA = arpPacket->getSrcMACAddress();
                       match->OFB_ARP_THA = arpPacket->getDestMACAddress();
                       match->OFB_ARP_SPA = arpPacket->getSrcIPAddress();
                       match->OFB_ARP_TPA = arpPacket->getDestIPAddress();
                   }


                   if (flow_table->lookup(match)){
                       //lookup successful
                       EV << "Found entry in flow table.\n" << endl;
                       ofp_action_output *action_output = flow_table->returnAction(match);
                       uint32_t outport = action_output->port;

                       send(frameBeingReceived, "ifOut", outport);
                   }
                    else {
                        // lookup fail; notification to Switch Application module
                       EV << "owner: " << frameBeingReceived->getOwner()->getFullName() << endl;
                       EV <<"queue in buffer" << endl;
                       drop(data_msg);
                       buffer->push(frameBeingReceived);
                       OF_Wrapper *dummy = new OF_Wrapper();
                       emit(NF_NO_MATCH_FOUND, dummy);
                   }


          }
 }

 void Open_Flow_Processing::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
 {
     Enter_Method_Silent();
     //printNotificationBanner(category, details);

     if (id==NF_FLOOD_PACKET)
     {
         //flood packet
             OF_Wrapper *wrapper = (OF_Wrapper *) obj;
             uint32_t buffer_id = wrapper->buffer_id;
             EV << "Processing buffer-id: " << buffer_id << endl;
             EthernetIIFrame *frame;
             if (buffer_id == OFP_NO_BUFFER)
             {
                 frame = wrapper->frame;
             }
             else
             {
                 frame = buffer->returnMessage(buffer_id);
             }
             take(frame);
             int n = gateSize("ifOut");
             //int numClients = getParentModule()->getParentModule()->par("numClients");
             for (int i=0; i<n; i++) {
                 if(i==frame->getArrivalGate()->getIndex() || (port_vector[i] == 0))
                     continue;
                 EthernetIIFrame *copy = frame->dup();
                 EV << "EthernetIIFrame ID: " << copy->getId() << endl;
                 send(copy, "ifOut", i);
//                 cDisplayString& connDispStr = getParentModule()->getParentModule()->gate("gate$o", i)->getDisplayString();
//                             connDispStr.parse("ls=red");
             }
             delete frame;

     }
     if (id==NF_SEND_PACKET)
     {
         // send packet on outport port
         OF_Wrapper *wrapper = (OF_Wrapper *) obj;
         uint32_t buffer_id = wrapper->buffer_id;
         uint16_t outport = wrapper->outport;
         EthernetIIFrame *frame;
         if (buffer_id == OFP_NO_BUFFER)
         {
             frame = wrapper->frame;
         }
         else
         {
             frame = buffer->returnMessage(buffer_id);
         }
         take(frame);
         send(frame, "ifOut", outport);
     }
 }

