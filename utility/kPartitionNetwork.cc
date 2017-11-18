#include "kPartitionNetwork.h"

Define_Module(kPartitionNetwork);


void kPartitionNetwork::initialize(int stage)
{
    if (stage==4)
    {
        numPartitions = par("numPartitions");
        WATCH_LIST(remainingVerts);

        const char *NodeType = par("NodeType");
        topo_nodetype.extractByNedTypeName(cStringTokenizer(NodeType).asVector());
        EV << "cTopology found " << topo_nodetype.getNumNodes() << " nodes\n";
        nodeInfo.resize(topo_nodetype.getNumNodes());
        for (int i= 0; i< topo_nodetype.getNumNodes(); i++)
        {
            for (int k = 0; k < topo_nodetype.getNode(i)->getNumOutLinks(); ++k) {
                int neighbor = getIndexForNode(topo_nodetype.getNode(i)->getLinkOut(k)->getRemoteNode());
                nodeInfo[i].neighbors.push_back(neighbor);
                ASSERT(neighbor>=0);
            }
            remainingVerts.push_back(i);

        }
        std::string cols[] = {"red","green","white","yellow","cyan","magenta","black"};

//        // First chose k random vertices
//        std::list<int>::iterator it;
//        int index=0;
//        sets.resize(numPartitions);
//        while(index<numPartitions){
//            it = remainingVerts.begin();
//            advance(it,intrand(remainingVerts.size()));
//            ASSERT(it!=remainingVerts.end());
//            sets[index].push_back(*it);
//            topo_nodetype.getNode(*it)->getModule()->par("domainID").setLongValue(index);
//            topo_nodetype.getNode(*it)->getModule()->getDisplayString().setTagArg("i", 1, cols[index].c_str());
//            remainingVerts.erase(it);
//
//            index++;
//        }
//        //reset index which is now used as global index
//        index=0;
//        while(remainingVerts.size()>0){
//            // Introduce optimization MinP-Greedy
//            // Chose next subset in such a way that minval(subset)= minimum minval(j): j element {0,...,numPartitions-1}
//            std::pair<int,int> out = findNextSubset(index);
//            index = out.first;
//            int next = out.second;
//            sets[index].push_back(next);
//            remainingVerts.remove(next);
//            topo_nodetype.getNode(next)->getModule()->par("domainID").setLongValue(index);
//            topo_nodetype.getNode(next)->getModule()->getDisplayString().setTagArg("i", 1, cols[index].c_str());
//        }
        // First chose one random vertices
        std::list<int>::iterator it;
        int index=0;
        sets.resize(numPartitions);

        if(par("oneRandomNode").boolValue()){
            it = remainingVerts.begin();
            if(par("startNode").longValue() >= 0 && par("startNode").longValue() < remainingVerts.size()){
                advance(it,par("startNode").longValue());
            }else{
                advance(it,intrand(remainingVerts.size()));
            }

            ASSERT(it!=remainingVerts.end());
            sets[index].push_back(*it);
            topo_nodetype.getNode(*it)->getModule()->par("domainID").setLongValue(index);
            topo_nodetype.getNode(*it)->getModule()->getDisplayString().setTagArg("i", 1, cols[index].c_str());
            EV << "Domain " <<  topo_nodetype.getNode(*it)->getModule()->getFullName() << " with ID " << topo_nodetype.getNode(*it)->getModule()->par("domainID").longValue() << endl;
            remainingVerts.erase(it);

        }else if(par("preferStubs").boolValue()){

            for (it = remainingVerts.begin(); it!= remainingVerts.end();it++){
                if(topo_nodetype.getNode(*it)->getNumOutLinks()==1){
                    sets[index].push_back(*it);
                    topo_nodetype.getNode(*it)->getModule()->par("domainID").setLongValue(index);
                    topo_nodetype.getNode(*it)->getModule()->getDisplayString().setTagArg("i", 1, cols[index].c_str());
                    EV << "Domain " <<  topo_nodetype.getNode(*it)->getModule()->getFullName() << " with ID " << topo_nodetype.getNode(*it)->getModule()->par("domainID").longValue() << endl;
                    it=remainingVerts.erase(it);
                    index++;
                }
                if(index==numPartitions)
                    break;
            }
            index=0;

        }else{
            // First chose k random vertices

            while(index<numPartitions){
                it = remainingVerts.begin();
                advance(it,intrand(remainingVerts.size()));
                ASSERT(it!=remainingVerts.end());
                sets[index].push_back(*it);
                topo_nodetype.getNode(*it)->getModule()->par("domainID").setLongValue(index);
                topo_nodetype.getNode(*it)->getModule()->getDisplayString().setTagArg("i", 1, cols[index].c_str());
                EV << "Domain " <<  topo_nodetype.getNode(*it)->getModule()->getFullName() << " with ID " << topo_nodetype.getNode(*it)->getModule()->par("domainID").longValue() << endl;
                remainingVerts.erase(it);
                index++;
            }
            //reset index which is now used as global index
            index=0;

        }

        while(remainingVerts.size()>0){
            // Introduce optimization MinP-Greedy
            // Chose next subset in such a way that minval(subset)= minimum minval(j): j element {0,...,numPartitions-1}
            std::pair<int,int> out = findNextSubset(index);
            index = out.first;
            int next = out.second;
            sets[index].push_back(next);
            remainingVerts.remove(next);
            topo_nodetype.getNode(next)->getModule()->par("domainID").setLongValue(index);
            topo_nodetype.getNode(next)->getModule()->getDisplayString().setTagArg("i", 1, cols[index].c_str());
            EV << "Domain " <<  topo_nodetype.getNode(next)->getModule()->getFullName() << " with ID " << topo_nodetype.getNode(next)->getModule()->par("domainID").longValue() << endl;
        }



    }
}

std::pair<int,int> kPartitionNetwork::findNextSubset(int startIndex){
    // Find next subset with minimimal vertex with minimal diff value
    // (i+startIndex+1)%numPartitions <-- i
    int min = numPartitions;
    int subset;
    int node;
    //int sum=0;
    unsigned int average = ceil((double)topo_nodetype.getNumNodes()/numPartitions);
//    for (int i = 0; i < numPartitions; ++i) {
//        sum += sets[i].size();
//    }
//    unsigned int average = ceil((double)sum/numPartitions);
    std::pair<int,int> temp;
    for (int i = 0; i < numPartitions; ++i) {
        temp = findNextVert(i);
        if(temp.second<min && sets[i].size() < average){
            min = temp.second;
            node = temp.first;
            subset = i;
        }

    }
    temp.first = subset;
    temp.second = node;
    return temp;
}

std::pair<int,int> kPartitionNetwork::findNextVert(int p){
    int min = numPartitions;
    int maxNeighbors = 0;
    int node;
    std::pair<int,int> output;
    std::list<int>::iterator it;
    for(it=remainingVerts.begin();it!=remainingVerts.end();it++){
        output=calcDiff(*it,p);
        if(output.first<min){
            min=output.first;
            node=*it;
            maxNeighbors=output.second;
        }else if(output.first==min && output.second>maxNeighbors){
            min=output.first;
            node=*it;
            maxNeighbors=output.second;
        }
    }
    output.first = node,
    output.second = min;
    return output;
}
/**
 * Returns diff value in first position and n value in second position
 */
std::pair<int,int> kPartitionNetwork::calcDiff(int node, int p){
    int diff = 0;
    std::pair<int,int> output;
    for (int i = 0; i < numPartitions; ++i) {
        if(i==p)
            continue;
        diff += calcN(node,i);
    }
    output.second = calcN(node,p);
    output.first = diff - output.second;
    return output;
}


int kPartitionNetwork::calcN(int node, int p){
    int n=0;
    std::vector<int>::iterator it;
    for ( it=nodeInfo[node].neighbors.begin() ; it < nodeInfo[node].neighbors.end(); it++ ){
        if(isContained(*it,sets[p]))
            n++;
    }
    return n;
}

bool kPartitionNetwork::isContained(int n, std::vector<int> vec){
    std::vector<int>::iterator it;
    for ( it=vec.begin() ; it < vec.end(); it++ ){
        if(*it==n)
            return true;
    }
    return false;
}

int kPartitionNetwork::getIndexForNode(cTopology::Node *n){
    for (int i= 0; i< topo_nodetype.getNumNodes(); i++)
    {
        if(topo_nodetype.getNode(i)==n)
            return i;

    }
    return -1;
}

void kPartitionNetwork::handleMessage(cMessage *msg)
{
    error("this module doesn't handle messages, it runs only in initialize()");
}
