/*
 * OFA_controller.h
 *
 *  Created on: 23.05.2012
 *      Author: rachor
 */

#ifndef OFA_CONTROLLER_H_
#define OFA_CONTROLLER_H_

#include <omnetpp.h>
#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include "messages/Open_Flow_Message_m.h"
#include "messages/OFP_Packet_In_m.h"


class OFA_controller: public cSimpleModule
{
public:
    OFA_controller();
    ~OFA_controller();
    void floodPacket(uint32_t buffer_id, OFP_Packet_In *packet_in_msg, int connID);
    void sendPacket(uint32_t buffer_id, OFP_Packet_In *packet_in_msg, uint32_t outport, int connID);
    void packet_out(cGate gate);
    void sendFlowModMessage(ofp_flow_mod_command mod_com, oxm_basic_match *match, uint32_t outport, int connID);
    void handshake(cMessage *msg);
    TCPSocket *findSocketFor(cMessage *msg);



protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void sendPacket(int numBytes, int expectedReplyBytes, bool serverClose = false);
    TCPSocket socket1;
    typedef std::map< int,TCPSocket * >   SocketMap;
    SocketMap  socketMap;
    void connect();
    void handleFeaturesReply(Open_Flow_Message *of_msg);
    void processQueuedMsg(cMessage *data_msg);



private:
    simsignal_t PacketInSignalId;
    simsignal_t connIDSignal;
    cListener *listener;

    bool busy;
    std::list<cMessage *> msg_list;
    double serviceTime;
};



#endif /* OFA_CONTROLLER_H_ */
