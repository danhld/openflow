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
// OpenFlow domain consisting of an OpenFlow switch, controller and several hosts.
//
module Domain_wController
{
    parameters:
        @display("bgb=347,267;i=misc/cloud;is=vs");
        int numClients = default(0);
        string ControllerType = default("Controller_Forwarding");
    gates:
        inout gate[] @labels(EtherFrame-conn);
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
        client[numClients]: StandardHost {

            @display("p=84,62,row,90");
        }
        controller: Open_Flow_Controller {
            @display("p=30,195");
        }
    connections allowunconnected:


        for i=0..sizeof(gate)-1 {
            gate[i] <--> open_flow_switch.ethg[i];
        }

        for i=0..numClients-1 {
            client[i].ethg++ <--> ethernetline <--> open_flow_switch.ethg[sizeof(gate)+i];
        }

        controller.ethg++ <--> ethernetline <--> open_flow_switch.gate_controller++;
}

