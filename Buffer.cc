#include <omnetpp.h>
#include "Buffer.h"
#include "openflow.h"

using namespace std;

Define_Module(Buffer);

Buffer::Buffer()
{

}

Buffer::~Buffer()
{


    msgdeque.clear();
    std::map<uint32_t, EthernetIIFrame *>::iterator i = pending_msgs.begin();
    while (i!=pending_msgs.end())
    {
        delete i->second;
        i++;
    }
    pending_msgs.clear();
}

bool Buffer::isfull() {
    return pending_msgs.size() >= capacity;
}

void Buffer::push(EthernetIIFrame *msg) {
    take(msg);
    msgdeque.push_back(msg);
}

EthernetIIFrame *Buffer::dequeue() {
    if (msgdeque.empty())
    {
        EV << "Buffer is empty.\n";
        return NULL;
    }
    EthernetIIFrame *pk = (EthernetIIFrame *)(msgdeque.front());
    msgdeque.pop_front();
    drop(pk);
    return pk;
}

// store message in buffer and return buffer_id.
uint32_t Buffer::storeMessage(EthernetIIFrame *msg)
{
    take(msg);
    pending_msgs.insert(pair<uint32_t, EthernetIIFrame *> (next_buffer_id, msg));
    char buf[80];
    sprintf(buf, "%d / %d pakets in buffer", pending_msgs.size(), capacity);
    getDisplayString().setTagArg("t", 0, buf);

    // OFP_NO_BUFFER = 0xffffffff;
    if (next_buffer_id < OFP_NO_BUFFER)
    {
        return next_buffer_id++;
    }
    else
    {
        next_buffer_id = 0;
        return next_buffer_id;
    }
}
bool Buffer::deleteMessage(EthernetIIFrame *msg)
{

    return true;
}

void Buffer::initialize() {
    capacity = par("capacity");
    next_buffer_id = 1;
}

uint32_t Buffer::getCapacity()
{
    return capacity;
}

// return message that is stored at the specified buffer_id
EthernetIIFrame *Buffer::returnMessage(uint32_t buffer_id)
{
    EthernetIIFrame *frame = (EthernetIIFrame *)pending_msgs[buffer_id];
    pending_msgs.erase(buffer_id);
    drop(frame);
    char buf[80];
    sprintf(buf, "%d / %d pakets in buffer", pending_msgs.size(), capacity);
    getDisplayString().setTagArg("t", 0, buf);
    return frame;


}

void Buffer::handleMessage(cMessage *msg)
{
    error("This module doesn't process messages");
}
