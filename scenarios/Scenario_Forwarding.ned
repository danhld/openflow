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

import openflow.nodes.Open_Flow_Controller;
import openflow.nodes.Open_Flow_Switch;
import inet.common.misc.ThruputMeteringChannel;
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;

network Scenario_Forwarding
{
    @display("bgb=780,513");

    types:
        channel ethernetline extends ThruputMeteringChannel  
        {
            delay = 1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "u";
        }
    submodules:
        client1: StandardHost {
            @display("p=39,35");
        }
        server1: StandardHost {
            @display("p=58,443");
        }
        configurator: FlatNetworkConfigurator {
            parameters:
                @display("p=280,454");
        }
        open_flow_switch: Open_Flow_Switch {
            @display("p=537,306");
        }
        controller: Open_Flow_Controller {
            @display("p=338,167");
        }

        server2: StandardHost {
            @display("p=661,225");
        }
        server3: StandardHost {
            @display("p=661,352");
        }
        open_flow_switch1: Open_Flow_Switch {
            @display("p=555,224");
        }
        open_flow_switch2: Open_Flow_Switch {
            @display("p=505,42");
        }
        server4: StandardHost {
            @display("p=661,43");
        }
        open_flow_switch3: Open_Flow_Switch {
            @display("p=304,54");
        }
        open_flow_switch4: Open_Flow_Switch {
            @display("p=128,114");
        }
        open_flow_switch5: Open_Flow_Switch {
            @display("p=485,384");
        }
        open_flow_switch6: Open_Flow_Switch {
            @display("p=210,410");
        }
        open_flow_switch7: Open_Flow_Switch {
            @display("p=128,332");
        }
        open_flow_switch9: Open_Flow_Switch {
            @display("p=119,192");
        }
        open_flow_switch10: Open_Flow_Switch {
            @display("p=381,397");
        }
    connections allowunconnected:

        open_flow_switch7.ethg++ <--> ethernetline <--> server1.ethg++;
        open_flow_switch1.ethg++ <--> ethernetline <--> server2.ethg++;
        open_flow_switch1.ethg++ <--> ethernetline <--> server3.ethg++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch.gate_controller++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch1.gate_controller++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch2.gate_controller++;
        open_flow_switch2.ethg++ <--> ethernetline <--> server4.ethg++;
        open_flow_switch.ethg++ <--> ethernetline <--> open_flow_switch1.ethg++;
        open_flow_switch3.gate_controller++ <--> ethernetline <--> controller.ethg++;
        open_flow_switch3.ethg++ <--> ethernetline <--> open_flow_switch2.ethg++;
        client1.ethg++ <--> ethernetline <--> open_flow_switch3.ethg++;
        open_flow_switch3.ethg++ <--> ethernetline <--> open_flow_switch4.ethg++;
        open_flow_switch4.gate_controller++ <--> ethernetline <--> controller.ethg++;
        open_flow_switch4.ethg++ <--> ethernetline <--> open_flow_switch9.ethg++;
        open_flow_switch7.ethg++ <--> ethernetline <--> open_flow_switch9.ethg++;
        open_flow_switch7.ethg++ <--> ethernetline <--> open_flow_switch6.ethg++;
        open_flow_switch5.ethg++ <--> ethernetline <--> open_flow_switch.ethg++;
        open_flow_switch6.ethg++ <--> ethernetline <--> open_flow_switch10.ethg++;
        open_flow_switch10.ethg++ <--> ethernetline <--> open_flow_switch5.ethg++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch9.gate_controller++;
        open_flow_switch7.gate_controller++ <--> ethernetline <--> controller.ethg++;
        open_flow_switch6.gate_controller++ <--> ethernetline <--> controller.ethg++;
        open_flow_switch10.gate_controller++ <--> ethernetline <--> controller.ethg++;
        open_flow_switch5.gate_controller++ <--> ethernetline <--> controller.ethg++;
}
