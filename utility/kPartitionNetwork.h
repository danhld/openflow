/*
 * minimalSpanningTree.h
 *
 *  Created on: 07.08.2012
 *      Author: rachor
 */

#ifndef KPARTITIONNETWORK_H_
#define KPARTITIONNETWORK_H_

#include <omnetpp.h>
using namespace omnetpp;

class kPartitionNetwork: public cSimpleModule {
protected:
    struct NodeInfo {
        NodeInfo() {
        }
        std::vector<int> neighbors;
    };
    typedef std::vector<NodeInfo> NodeInfoVector;
    cTopology topo_nodetype;
    NodeInfoVector nodeInfo;
    int numPartitions;
    std::vector<std::vector<int> >sets;
    std::list<int> remainingVerts;

    virtual std::pair<int,int> findNextVert(int p);
    virtual std::pair<int,int> findNextSubset(int startIndex);
    virtual int getIndexForNode(cTopology::Node *n);
    virtual bool isContained(int n, std::vector<int> vec);
    virtual int calcN(int node, int p);
    virtual std::pair<int,int> calcDiff(int node, int p);
    virtual int numInitStages() const {
        return 5;
    }
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
};

#endif
