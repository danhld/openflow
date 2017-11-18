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

package openflow.scenarios;

import inet.node.ethernet.EtherSwitch;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.common.misc.ThruputMeteringChannel;
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;


import openflow.nodes.*;


network Scenario_Small
{
    @display("bgb=469,309");

    types:
        channel ethernetline extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "u";
        }
    submodules:
        client1: StandardHost {
            @display("p=39,158");
        }
        server1: StandardHost {
            @display("p=376,98");
        }
        configurator: FlatNetworkConfigurator {
            parameters:
                @display("p=195,236");
        }
        open_flow_switch: Open_Flow_Switch {
            @display("p=143,158");
        }
        controller: Open_Flow_Controller {
            @display("p=182,41");
        }

        server2: StandardHost {
            @display("p=376,158");
        }
        server3: StandardHost {
            @display("p=376,228");
        }
        open_flow_switch1: Open_Flow_Switch {
            @display("p=273,158");
        }
    connections allowunconnected:

//        client1.ethg++ <--> {delay=1ms;} <--> open_flow_switch.ethg++;
//        open_flow_switch.ethg++ <--> {delay=1ms;} <--> server1.ethg++;
//        controller.ethg++ <--> {delay=1ms;} <--> open_flow_switch.gate_controller++;
//        open_flow_switch.ethg++ <--> {delay=1ms;} <--> server2.ethg++;
//        open_flow_switch.ethg++ <--> {delay=1ms;} <--> server3.ethg++;

        client1.ethg++ <--> ethernetline <--> open_flow_switch.ethg++;
        open_flow_switch1.ethg++ <--> ethernetline <--> server1.ethg++;
        open_flow_switch1.ethg++ <--> ethernetline <--> server2.ethg++;
        open_flow_switch1.ethg++ <--> ethernetline <--> server3.ethg++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch.gate_controller++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch1.gate_controller++;
        open_flow_switch.ethg++ <--> ethernetline <--> open_flow_switch1.ethg++;
}
