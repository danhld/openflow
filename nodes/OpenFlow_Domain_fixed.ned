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

import inet.node.inet.StandardHost;
import inet.common.misc.ThruputMeteringChannel;
import openflow.*;
//
// OpenFlow domain with fixed number of controller connections
//
module OpenFlow_Domain_fixed
{
    parameters:
        @display("bgb=347,267;i=misc/cloud;is=vs");
        int numClients = default(0);
        int domainID = default(-1);

    gates:
        inout gate[] @labels(EtherFrame-conn);
        inout gate_controller @labels(Controller-conn);
    types:
        channel ethernetline extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "u";
        }
    submodules:
        open_flow_switch: Open_Flow_Switch {
            @display("p=168,186");
            gates:
                ethg[sizeof(gate)+numClients];
        }
        //        client2: StandardHost {
        //            numTcpApps = 1;
        //            tcpAppType = default("TCPSinkApp");
        ////            tcpApp[0].port = 1000;
        //            @display("p=188,57");
        //        }
        //        client1: StandardHost {
        //            numTcpApps = 1;
        //            tcpAppType = default("TCPSinkApp");
        ////            tcpApp[0].port = 1000;
        //            @display("p=271,96");
        //        }
        //        client3: StandardHost {
        //            numTcpApps = 1;
        //            tcpAppType = default("TCPSinkApp");
        ////            tcpApp[0].port = 1000;
        //            @display("p=76,86");
        //        }
        client[numClients]: StandardHost {
            @display("p=24,82,row,90");
        }
    connections allowunconnected:
        for i=0..sizeof(gate)-1 {
            gate[i] <--> open_flow_switch.ethg[i];
        }

        for i=0..numClients-1 {
            client[i].ethg++ <--> ethernetline <--> open_flow_switch.ethg[sizeof(gate)+i];
        }



        gate_controller <--> ethernetline <--> open_flow_switch.gate_controller++;
//        for i=0..sizeof(gate_controller)-1 {
//            gate_controller[i] <--> open_flow_switch.gate_controller++;
//        }
}

