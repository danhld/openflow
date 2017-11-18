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
import openflow.utility.SpanningTree;

network Scenario_SPT_Small
{
    @display("bgb=620,561");

    types:
        channel ethernetline extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "u";
        }
    submodules:
        server3: StandardHost {
            @display("p=39,106");
        }
        server1: StandardHost {
            @display("p=415,75");
        }
        configurator: FlatNetworkConfigurator {
            parameters:
                @display("p=153,522");
        }
        open_flow_switch: Open_Flow_Switch {
            @display("p=97,171");
        }
        controller: Open_Flow_Controller {
            @display("p=139,69");
        }

        server2: StandardHost {
            @display("p=415,152");
        }
        client: StandardHost {
            @display("p=49,366");
        }
        open_flow_switch1: Open_Flow_Switch {
            @display("p=305,158");
        }
        open_flow_switch2: Open_Flow_Switch {
            @display("p=249,318");
        }
        server4: StandardHost {
            @display("p=415,319");
        }
        open_flow_switch3: Open_Flow_Switch {
            @display("p=122,293");
        }
        open_flow_switch4: Open_Flow_Switch {
            @display("p=288,55");
        }
        open_flow_switch5: Open_Flow_Switch {
            @display("p=305,244");
        }
        spanningTree: SpanningTree {
            @display("p=64,498");
        }
    connections allowunconnected:

        server3.ethg++ <--> ethernetline <--> open_flow_switch.ethg++;
        open_flow_switch4.ethg++ <--> ethernetline <--> server1.ethg++;
        open_flow_switch1.ethg++ <--> ethernetline <--> server2.ethg++;
        open_flow_switch3.ethg++ <--> ethernetline <--> client.ethg++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch.gate_controller++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch1.gate_controller++;
        open_flow_switch.ethg++ <--> ethernetline <--> open_flow_switch1.ethg++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch2.gate_controller++;
        open_flow_switch2.ethg++ <--> ethernetline <--> server4.ethg++;
        open_flow_switch.ethg++ <--> ethernetline <--> open_flow_switch3.ethg++;
        open_flow_switch3.ethg++ <--> ethernetline <--> open_flow_switch2.ethg++;
        open_flow_switch3.ethg++ <--> ethernetline <--> open_flow_switch1.ethg++;
        open_flow_switch3.gate_controller++ <--> ethernetline <--> controller.ethg++;
        controller.ethg++ <--> ethernetline <--> open_flow_switch4.gate_controller++;
        open_flow_switch3.ethg++ <--> ethernetline <--> open_flow_switch4.ethg++;
        open_flow_switch4.ethg++ <--> ethernetline <--> open_flow_switch1.ethg++;
        open_flow_switch2.ethg++ <--> ethernetline <--> open_flow_switch5.ethg++;
        open_flow_switch5.ethg++ <--> ethernetline <--> open_flow_switch1.ethg++;
        open_flow_switch5.gate_controller++ <--> ethernetline <--> controller.ethg++;
}
