//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package openflow.nodes;

//import inet.base.NotificationBoard;
//import inet.linklayer.ethernet.EthernetInterface;
//import inet.networklayer.ipv4.RoutingTable;
//import inet.nodes.inet.NetworkLayer;
//import inet.transport.ITCP;
//import inet.networklayer.contract.INetworkLayer;
//import inet.networklayer.contract.IRoutingTable;
import inet.networklayer.common.InterfaceTable;

import inet.transportlayer.contract.ITCP;
import inet.linklayer.ppp.PPPInterface;
import inet.linklayer.ethernet.EthernetInterface;
import inet.linklayer.loopback.LoopbackInterface;
import inet.networklayer.ipv4.*;

import openflow.*;
import openflow.ctrlApps.*;
//
// TODO documentation
//
module Open_Flow_Controller
{
    parameters:
        
//        @node(); 
		@networkNode; //Inet 3.6 changed @node to @networkNode
        @labels(node,ethernet-node);
        @display("i=device/server;bgb=843,453;i2=OpenFlow-Logo-small");
        int numTcpApps = default(0);
        int numUdpApps = default(0);
        int numSctpApps = default(0);

        string tcpAppType = default("n/a");
        string udpAppType = default("n/a");
        string sctpAppType = default("n/a");

        string behavior = default("Switch");
        string tcpType = default("TCP");  // tcp implementation (e.g. TCP, TCP_old, TCP_NSC)
        //        bool IPForward = default(false);
        int namid = default(-1);
        string routingFile = default("");
        int numExtInterfaces = default(0);
        double serviceTime @unit("s") = default(0s);
        int domainID = default(-1);

//DANH added:

        bool hasTcp = default(numTcpApps > 0);
        bool hasUdp = default(numUdpApps > 0);
        bool hasSctp = default(numSctpApps > 0);
        bool forwarding = default(false);  // disable routing by default
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        *.routingTableModule = default(absPath(".routingTable"));

    gates:
        inout ethg[] @labels(EtherFrame-conn);
    submodules:

//        
//        notificationBoard: NotificationBoard {
//            parameters:
//                @display("p=57,54");
//        }

//        ppp[sizeof(pppg)]: PPPInterface {
//            parameters:
//                @display("p=139,282,row,110;q=l2queue;i=block/ifcard");
//        }



        tcp: <tcpType> like ITCP if hasTcp {
            parameters:
                @display("p=153.51875,165.165");
        }


        interfaceTable: InterfaceTable { 
            parameters:
                @display("p=51,216;i=block/table");
        }

        routingTable: IPv4RoutingTable {
            parameters:
                forwarding = forwarding;
                routerId = "";
                routingFile = routingFile;
                @display("p=51,124;i=block/table");
        }
        networkLayer: IPv4NetworkLayer {
            parameters:
                proxyARP = false;
                @display("p=330.33,257.27625;q=queue");
            gates:
                ifIn[sizeof(pppg)+sizeof(ethg)+numExtInterfaces];
                ifOut[sizeof(pppg)+sizeof(ethg)+numExtInterfaces];
        }

        eth[sizeof(ethg)]: EthernetInterface {
            parameters:
                @display("p=330.33,397.03125,row,90;q=txQueue");
        }
        ofa_controller: OFA_controller {
            @display("p=153.51875,38.114998");
            serviceTime = serviceTime;
        }
        ctrlApp: <behavior> like CtrlBehavior {
            @display("p=330.33,38.114998");
        }
    connections allowunconnected:
        tcp.ipOut --> networkLayer.transportIn++ if hasTcp;
        tcp.ipIn <-- networkLayer.transportOut++ if hasTcp;

        for i=0..sizeof(ethg)-1 {
            ethg[i] <--> eth[i].phys;
            eth[i].upperLayerOut --> networkLayer.ifIn[i];
            eth[i].upperLayerIn <-- networkLayer.ifOut[i];
        }

        tcp.appOut++ --> ofa_controller.tcpIn;
        ofa_controller.tcpOut --> tcp.appIn++;
}


