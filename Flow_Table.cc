#include <omnetpp.h>
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "inet/linklayer/common/MACAddress.h"
#include "inet/networklayer/arp/ipv4/ARPPacket_m.h"
#include "Flow_Table.h"
#include <list>
using namespace std;



Define_Module(Flow_Table);

// int oxm_basic_match::getPriority()
// {
//     int sum = 0;
//     for (int i=0; i < 4; i++)
//     {
//         sum += wildcards[i];
//     }
//     return 0;
// }

Flow_Table::Flow_Table() {

}

static inline int flow_fields_match(oxm_basic_match *m1, oxm_basic_match *m2, uint32_t w)
{

    return (((w & OFPFW_IN_PORT) || m1->OFB_IN_PORT == m2->OFB_IN_PORT)
            && ((w & OFPFW_DL_TYPE) || m1->OFB_ETH_TYPE == m2->OFB_ETH_TYPE )
            && ((w & OFPFW_DL_SRC) || !m1->OFB_ETH_SRC.compareTo(m2->OFB_ETH_SRC))
            && ((w & OFPFW_DL_DST) || !m1->OFB_ETH_DST.compareTo(m2->OFB_ETH_DST)));
}

void Flow_Table::addEntry(oxm_basic_match *match, entry_data* data) {


    pair<multimap<oxm_basic_match, entry_data>::iterator, bool> ret;
    entry_map.insert(pair<oxm_basic_match, entry_data>(*match, *data));


    std::multimap<oxm_basic_match, entry_data>::iterator j = entry_map.begin();

    while (j!=entry_map.end())
    {
        EV << j->first.OFB_IN_PORT  <<endl;
        EV << j->first.OFB_ETH_SRC  <<endl;
        EV << j->first.OFB_ETH_DST  <<endl;
        EV << j->first.OFB_ETH_TYPE  <<endl;
        j++;
    }

    EV << "Number of entries in "<< this->getFullName()<< ":"  <<entry_map.size() << endl;
    size = entry_map.size();
}


bool Flow_Table::deleteEntry(oxm_basic_match *match)
{

    EV << "Number of entries in "<< this->getFullName()<< ":"  <<entry_map.size() << endl;

    multimap<oxm_basic_match, entry_data>::iterator iter = entry_map.begin();
    while (iter != entry_map.end()) {
        oxm_basic_match *m = const_cast<oxm_basic_match*> (&iter->first);
        if (flow_fields_match(match, m, iter->first.wildcards))

        {
            entry_map.erase(iter);
            delete match;
            size = entry_map.size();

            EV << "Number of entries in "<< this->getFullName()<< ":"  <<entry_map.size() << endl;
            return true;
        }
        iter++;
    }
    EV << "Number of entries in "<< this->getFullName()<< ":"  <<entry_map.size() << endl;
    return false;
}

void Flow_Table::initialize()
{
    size = 0;
    WATCH(size);
}



bool Flow_Table::lookup(oxm_basic_match *match)
{
    EV << "lookup \n";
    map<oxm_basic_match, entry_data>::iterator iter = entry_map.begin();
    while (iter != entry_map.end()) {
        oxm_basic_match *m = const_cast<oxm_basic_match*> (&iter->first);
        if (flow_fields_match(match, m, iter->first.wildcards))
            return true;
        iter++;
    }
    return false;
}

ofp_action_output *Flow_Table::returnAction(oxm_basic_match *match)
{
    map<oxm_basic_match, entry_data>::iterator iter = entry_map.begin();
    while (iter != entry_map.end()) {
        oxm_basic_match *m = const_cast<oxm_basic_match*> (&iter->first);
        if (flow_fields_match(match, m, iter->first.wildcards))
            return &iter->second.instruc->actions[0];
        iter++;
    }
    return NULL;
}
void Flow_Table::handleMessage(cMessage *msg)
{
    error("This module doesn't process messages");
}
