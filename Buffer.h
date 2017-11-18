/*
 * buffer.h
 *
 *  Created on: 10.05.2012
 *      Author: rachor
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <deque>
#include <map>
#include "inet/linklayer/ethernet/EtherFrame_m.h"


using namespace std;
using namespace inet;

class Buffer : public cSimpleModule
{
public:
    Buffer();
    ~Buffer();
    bool isfull();
    void push(EthernetIIFrame *msg);
    EthernetIIFrame *dequeue();
    uint32_t storeMessage(EthernetIIFrame *msg);
    bool deleteMessage(EthernetIIFrame *msg);
    EthernetIIFrame *returnMessage(uint32_t buffer_id);
    uint32_t getCapacity();


protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

private:
    std::deque<EthernetIIFrame *> msgdeque;
    std::map<uint32_t, EthernetIIFrame *> pending_msgs;
    uint32_t capacity;
    uint32_t next_buffer_id;
};




#endif /* BUFFER_H_ */
