#include "SpanningTree.h"
#include "Open_Flow_Processing.h"

Define_Module(SpanningTree);

bool selectFunction(cModule *mod, void *v_ptr){
    int id = *(int *)v_ptr;

    return strcmp(mod->getNedTypeName(),"openflow.nodes.OpenFlow_Domain_fixed")==0 &&
            mod->par("domainID").longValue()==id;

}

void SpanningTree::initialize(int stage) {
    if (stage == 4) {
        const char *NodeType = par("NodeType");
        int startNode = par("startNode");
        int domainID = par("domainID");

        if(domainID>=0){
            topo_spanntree.extractFromNetwork(selectFunction, (int *) &domainID);
            EV << "cTopology found " << topo_spanntree.getNumNodes() << " domains for domainID " << domainID << "\n";
        }else{
            topo_spanntree.extractByNedTypeName(
                    cStringTokenizer(NodeType).asVector());
            EV << "cTopology found " << topo_spanntree.getNumNodes() << "\n";
        }

        nodeInfo.resize(topo_spanntree.getNumNodes());
        for (int i = 0; i < topo_spanntree.getNumNodes(); i++) {
            nodeInfo[i].moduleID = topo_spanntree.getNode(i)->getModuleId();
            nodeInfo[i].treeNeighbors.resize(topo_spanntree.getNumNodes(),0);

        }

        // start node for calculation of spanning tree
        if(startNode < topo_spanntree.getNumNodes()){
            nodeInfo[startNode].isInTree = true;
        }else{
            nodeInfo[intrand(topo_spanntree.getNumNodes())].isInTree = true;
        }

        int counter = 0;
        while (counter != topo_spanntree.getNumNodes()) {
            counter = 0;
            for (int i = 0; i < topo_spanntree.getNumNodes(); i++) {

                if (nodeInfo[i].isProcessed) {
                    counter++;
                }

                if (nodeInfo[i].isInTree && !nodeInfo[i].isProcessed) {
                    EV << "Processing node " << topo_spanntree.getNode(i)->getModule()->getName() << " with index "<< i << ".\n";
                    nodeInfo[i].isProcessed = true;
                    // for loop over all neighbors
                    for (int j = 0; j < topo_spanntree.getNode(i)->getNumOutLinks(); j++) {
                        // for loop over all nodes to identify neighbors
                        for (int x = 0; x < topo_spanntree.getNumNodes(); x++) {
                            // test, if node x is neighbor of node i by using moduleID and is not yet in tree
                            if (nodeInfo[x].moduleID
                                    == topo_spanntree.getNode(i)->getLinkOut(j)->getRemoteNode()->getModuleId())
                            {
                                if(!nodeInfo[x].isInTree){
                                    // Neighbor is not yet in tree and will be added
                                    nodeInfo[x].isInTree = true;
                                    nodeInfo[x].treeNeighbors[i]=1;

                                }else{
                                    if(nodeInfo[i].treeNeighbors[x]== 1){
                                        // Link is already part of spanning tree and must not be disabled
                                        continue;
                                    }
                                    // Neighbor is already in tree, deactivate corresponding link
                                    nodeInfo[i].ports.push_back(topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex());
                                    EV << "Disable link with index " << topo_spanntree.getNode(i)->getLinkOut(j)->getLocalGate()->getIndex() <<
                                            " at node " << i << " to node " << x << "!" << endl;

                                }
                            }
                        }

                    }

                }
            }

        }
        // disable ports for all nodes
        for (int x = 0; x < topo_spanntree.getNumNodes(); x++) {
            // Find open_flow_processing module within submodules
            if (topo_spanntree.getNode(x)->getModule()->findSubmodule(
                    "open_Flow_Processing")>=0) {
                cModule *mod =
                        topo_spanntree.getNode(x)->getModule()->getSubmodule(
                                "open_Flow_Processing");
                Open_Flow_Processing *proc = check_and_cast<
                        Open_Flow_Processing *>(mod);
                proc->disablePorts(nodeInfo[x].ports);
            } else if (topo_spanntree.getNode(x)->getModule()->findSubmodule(
                    "open_flow_switch")>=0) {
                cModule *mod =
                        topo_spanntree.getNode(x)->getModule()->getSubmodule(
                                "open_flow_switch")->getSubmodule(
                                "open_Flow_Processing");
                Open_Flow_Processing *proc = check_and_cast<
                        Open_Flow_Processing *>(mod);
                proc->disablePorts(nodeInfo[x].ports);
            }
        }
    }
}

void SpanningTree::handleMessage(cMessage *msg) {
    error("this module doesn't handle messages, it runs only in initialize()");
}
