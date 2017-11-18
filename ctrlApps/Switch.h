/*
 * Switch.h
 *
 *  Created on: 08.06.2012
 *      Author: rachor
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "OFA_controller.h"
#include "inet/linklayer/common/MACAddress.h"

struct MAC_connID
{
    MACAddress address;
    int connID;
};

struct ltmatch
{
    bool operator() (const MAC_connID m1, const MAC_connID m2) const
    {
        return m1.address.compareTo(m2.address);
    }
};

class Switch: public cSimpleModule, public cListener
{
public:
    Switch();
    ~Switch();
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

protected:
    virtual void initialize();


private:
    OFA_controller *controller;
    std::multimap<MAC_connID, uint32_t, ltmatch> mac_to_port;
};


#endif /* SWITCH_H_ */
