#include "placeController.h"
#include "Open_Flow_Processing.h"

Define_Module(placeController);


void placeController::initialize(int stage)
{
    if (stage==4)
    {
        topo.extractByNedTypeName(cStringTokenizer(par("domainNedType")).asVector());
        EV << "cTopology found " << topo.getNumNodes() << " nodes\n";

        if(par("location_index").longValue()>=0){
            location_index = par("location_index").longValue();
        }else{
            location_index = intrand(topo.getNumNodes());
        }

        nodeInfo.resize(topo.getNumNodes());
        if (location_index < topo.getNumNodes())
        {
            // destNode = controller location
            cTopology::Node *destNode = topo.getNode(location_index);
            char buf[80];
                        sprintf(buf, "controller location: %s ", destNode->getModule()->getFullPath().c_str());
                        getDisplayString().setTagArg("t", 0, buf);

            topo.calculateUnweightedSingleShortestPathsTo(destNode);
            nodeInfo[location_index].moduleID = topo.getNode(location_index)->getModuleId();
            for (int j=0; j<topo.getNumNodes(); j++)
            {
                if (location_index==j) continue;
                cTopology::Node *atNode = topo.getNode(j);
                if (atNode->getNumPaths()==0)
                    continue; // not connected
                while (atNode!=destNode)
                {
                    // sum up delay of all links of the path to controller
                    cDatarateChannel *dchannel = (cDatarateChannel *) atNode->getPath(0)->getLocalGate()->getChannel();
                    nodeInfo[j].delay += dchannel->getDelay();
                    atNode = atNode->getPath(0)->getRemoteNode();
                }
                // set delay for both directions
                cDatarateChannel *dchannel = (cDatarateChannel *)topo.getNode(j)->getModule()->gate("gate_controller$o", 0)->getChannel();
                dchannel->setDelay(nodeInfo[j].delay.dbl());
                dchannel = (cDatarateChannel *)topo.getNode(j)->getModule()->gate("gate_controller$i", 0)->getPreviousGate()->getChannel();
                                dchannel->setDelay(nodeInfo[j].delay.dbl());
            }
        }
    }
}



void placeController::handleMessage(cMessage *msg)
{
    error("this module doesn't handle messages, it runs only in initialize()");
}
