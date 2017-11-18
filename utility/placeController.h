/*
 * placeController.h
 *
 *  Created on: 03.08.2012
 *      Author: rachor
 */

#ifndef PLACECONTROLLER_H_
#define PLACECONTROLLER_H_

#include <omnetpp.h>

using namespace omnetpp;

class placeController : public cSimpleModule
{
protected:
    struct NodeInfo {
            NodeInfo() {delay = 0;}

            int moduleID;



            simtime_t delay;
        };
        typedef std::vector<NodeInfo> NodeInfoVector;
        cTopology topo;
        NodeInfoVector nodeInfo;

        virtual int numInitStages() const  {return 5;}
            virtual void initialize(int stage);
            virtual void handleMessage(cMessage *msg);
            int location_index;
};



#endif /* PLACECONTROLLER_H_ */
