/*
 * Forwarding.h
 *
 *  Created on: 05.07.2012
 *      Author: rachor
 */

#ifndef FORWARDING_H_
#define FORWARDING_H_


#include "OFA_controller.h"
#include "inet/linklayer/common/MACAddress.h"
#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/ipv4/IPv4Address.h"


#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/configurator/ipv4/FlatNetworkConfigurator.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/ipv4/IPv4InterfaceData.h"
#include "inet/networklayer/ipv4/IIPv4RoutingTable.h"
#include "inet/networklayer/contract/IRoutingTable.h"

#include <vector>
#include <algorithm>



class IInterfaceTable;
//class IRoutingTable;
class IIPv4RoutingTable;

using namespace inet;

class Forwarding: public cSimpleModule, public cListener
{
public:
    Forwarding();
    ~Forwarding();
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

protected:
    virtual void initialize(int stage);

protected:
    struct NodeInfo {
        bool isIPNode;
        bool isOpenFlow;
        inet::IInterfaceTable *ift;
        inet::IIPv4RoutingTable *rt; //DANH changed from inet::IRoutingTable *rt; upgrade to IRoutingTable later
        IPv4Address address;
        MACAddress macAddress;
        bool usesDefaultRoute;
        int connID;
        std::string name;
        friend std::ostream& operator<<(std::ostream& os, NodeInfo ni)
        {
            os << "Name: " << ni.name <<", MAC: " << ni.macAddress << ", IP: " << ni.address << ", connID: " << ni.connID << endl;
            return os;
        }
        NodeInfo() {isIPNode=false;ift=NULL;rt=NULL;usesDefaultRoute=false;}
    };
    typedef std::vector<NodeInfo> NodeInfoVector;

    virtual void extractTopology(cTopology& topo, NodeInfoVector& nodeInfo);
    virtual void assignAddresses(cTopology& topo, NodeInfoVector& nodeInfo);
    virtual bool processARPPacket(OFP_Packet_In *packet_in, int connID);

    virtual int numInitStages() const  {return 5;}

    simsignal_t connIDSignal;
    simsignal_t PacketInSignalId;

    cTopology topo_forw;
    NodeInfoVector nodeInfo;
    bool isArpOracle;


private:
    OFA_controller *controller;
    typedef std::vector<std::pair<int, uint32_t> > UnsortedMap;
    UnsortedMap connID_outport;

};



#endif /* FORWARDING_H_ */
