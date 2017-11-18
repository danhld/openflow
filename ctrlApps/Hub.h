/*
 * Hub.h
 *
 *  Created on: 31.05.2012
 *      Author: rachor
 */

#ifndef HUB_H_
#define HUB_H_

#include "OFA_controller.h"

class Hub: public cSimpleModule, public cListener
{
public:
    Hub();
    ~Hub();
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

protected:
    virtual void initialize();


private:
    OFA_controller *controller;
};


#endif /* HUB_H_ */
