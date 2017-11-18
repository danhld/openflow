/*
 * OFA_switch.h
 *
 *  Created on: 11.05.2012
 *      Author: rachor
 */

#ifndef OFA_SWITCH_H_
#define OFA_SWITCH_H_

#include <omnetpp.h>
#include <Buffer.h>
//#include <INotifiable.h>
#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include "openflow.h"
#include "messages/Open_Flow_Message_m.h"
#include "Flow_Table.h"
#include "Open_Flow_Processing.h"


class OFA_switch: public cSimpleModule, public cListener
{
public:
    OFA_switch();
    ~OFA_switch();
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);



protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void handlePacket();
    void sendPacketInMessage(EthernetIIFrame *frame,  uint32_t buffer_id,int numBytes);
    TCPSocket socket;

    void connect();
    void handleTimer(cMessage *msg);
    void handleFeaturesRequestMessage(Open_Flow_Message *of_msg);

    void execute_packet_out_action(ofp_action_header *action, uint32_t buffer_id, uint32_t inport);
    void execute_packet_out_action(ofp_action_header *action, EthernetIIFrame *frame, uint32_t inport);
    void handlePacketOutMessage(Open_Flow_Message *of_msg);
    void handleFlowModMessage(Open_Flow_Message *of_msg);


private:
    Buffer *buffer;
    cMessage *  timeoutMsg;
    Flow_Table *flow_table;
    double timeout;
    simsignal_t NF_FLOOD_PACKET;
    simsignal_t NF_SEND_PACKET;
    simsignal_t NF_NO_MATCH_FOUND;

};


#endif /* OFA_SWITCH_H_ */
