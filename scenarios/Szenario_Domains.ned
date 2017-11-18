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
//import inet.util.ThruputMeteringChannel;
import ned.DatarateChannel;
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;

import openflow.utility.kPartitionNetwork;
import openflow.nodes.*;
import openflow.DistanceChannel;
import openflow.utility.SpanningTree;
import openflow.utility.placeController;


network Scenario_singleController
{
    @display("bgb=842,642;bgi=maps/usa");

	types:
        channel backboneline extends DatarateChannel //ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 40Gbps;
//            thruputDisplayFormat = "u";
        }
    submodules:
        configurator: FlatNetworkConfigurator {
            parameters:
                @display("p=332,565");
        }
        controller: Open_Flow_Controller {
            @display("p=376,184");
        }
        //		0
        ofs_Vancouver: OpenFlow_Domain {
            @display("p=108,10");
        }
        //		1
        ofs_Seattle: OpenFlow_Domain {
            @display("p=78,49");
        }

        //		2
        ofs_Portland: OpenFlow_Domain {
            @display("p=69,88");
        }

        //		3
        ofs_Sunnyvale: OpenFlow_Domain {
            @display("p=39,254");
        }

        //		4
        ofs_LosAngeles: OpenFlow_Domain {
            @display("p=66,287");
        }

        //		5
        ofs_Missoula: OpenFlow_Domain {
            @display("p=187,88");
        }

        //		6
        ofs_SaltLakeCity: OpenFlow_Domain {
            @display("p=168,207");
        }

        //		7
        ofs_Phoenix: OpenFlow_Domain {
            @display("p=150,314");
        }

        //		8
        ofs_Denver: OpenFlow_Domain {
            @display("p=250,234");
        }

        //		9
        ofs_Albuqerque: OpenFlow_Domain {
            @display("p=230,293");
        }

        //		10
        ofs_ElPaso: OpenFlow_Domain {
            @display("p=257,363");
        }

        //		11
        ofs_Minneapolis: OpenFlow_Domain {
            @display("p=415,135");
        }

        //		12
        ofs_KansasCity: OpenFlow_Domain {
            @display("p=396,246");
        }

        //		13
        ofs_Dallas: OpenFlow_Domain {
            @display("p=376,347");
        }

        //		14
        ofs_Houston: OpenFlow_Domain {
            @display("p=415,404");
        }

        //		15
        ofs_Chicago: OpenFlow_Domain {
            @display("p=483,184");
        }

        //		16
        ofs_Indianapolis: OpenFlow_Domain {
            @display("p=522,223");
        }

        //		17
        ofs_Louisville: OpenFlow_Domain {
            @display("p=528,254");
        }

        //		18
        ofs_Nashville: OpenFlow_Domain {
            @display("p=504,301");
        }
        //		19
        ofs_Memphis: OpenFlow_Domain {
            @display("p=465,314");
        }
        //		20
        ofs_Jackson: OpenFlow_Domain {
            @display("p=465,363");
        }

        //		21
        ofs_BatonRouge: OpenFlow_Domain {
            @display("p=468,390");
        }

        //		22
        ofs_Cleveland: OpenFlow_Domain {
            @display("p=576,174");
        }

        //		23
        ofs_Pittsburgh: OpenFlow_Domain {
            @display("p=600,196");
        }
        //		24
        ofs_Atlanta: OpenFlow_Domain {
            @display("p=549,332");
        }
        //		25
        ofs_Jacksonville: OpenFlow_Domain {
            @display("p=600,378");
        }
        //		26
        ofs_Buffalo: OpenFlow_Domain {
            @display("p=607,156");
        }
        //		27
        ofs_Ashburn: OpenFlow_Domain {
            @display("p=623,207");
        }
        //		28
        ofs_Raleigh: OpenFlow_Domain {
            @display("p=632,275");
        }

        //		29
        ofs_WashingtonDC: OpenFlow_Domain {
            @display("p=655,215");
        }

        //		30
        ofs_Miami: OpenFlow_Domain {
            @display("p=632,443");
        }
        //		31
        ofs_Philadelphia: OpenFlow_Domain {
            @display("p=655,196");
        }
        //		32
        ofs_NewYork: OpenFlow_Domain {
            @display("p=681,174");
        }
        //		33
//        ofs_Bridgeport: OpenFlow_Domain {
//            @display("p=706,162");
//        }

        //		33
        ofs_Boston: OpenFlow_Domain {
            @display("p=720,135");
        }

        spanningTree: SpanningTree {
            @display("p=90,565");
        }
        placeController: placeController {
            @display("p=619,565");
        }
    connections allowunconnected:

        ofs_LosAngeles.gate++ <--> DistanceChannel {  distance = 575km; } <--> ofs_Phoenix.gate++;
        ofs_Phoenix.gate++ <--> DistanceChannel {  distance = 557km; } <--> ofs_ElPaso.gate++;
        ofs_ElPaso.gate++ <--> DistanceChannel {  distance = 369km; } <--> ofs_Albuqerque.gate++;
        ofs_ElPaso.gate++ <--> DistanceChannel {  distance = 1087km; } <--> ofs_Houston.gate++;
        ofs_Albuqerque.gate++ <--> DistanceChannel {  distance = 537km; } <--> ofs_Denver.gate++;
        ofs_Denver.gate++ <--> DistanceChannel {  distance = 898km; } <--> ofs_KansasCity.gate++;
        ofs_Missoula.gate++ <--> DistanceChannel {  distance = 1617km; } <--> ofs_Minneapolis.gate++;
        ofs_Minneapolis.gate++ <--> DistanceChannel {  distance = 572km; } <--> ofs_Chicago.gate++;
        ofs_Houston.gate++ <--> DistanceChannel {  distance = 362km; } <--> ofs_Dallas.gate++;
        ofs_Dallas.gate++ <--> DistanceChannel {  distance = 729km; } <--> ofs_KansasCity.gate++;
        ofs_KansasCity.gate++ <--> DistanceChannel {  distance = 662km; } <--> ofs_Chicago.gate++;
        ofs_Chicago.gate++ <--> DistanceChannel {  distance = 263km; } <--> ofs_Indianapolis.gate++;
        ofs_Houston.gate++ <--> DistanceChannel {  distance = 413km; } <--> ofs_BatonRouge.gate++;
        ofs_BatonRouge.gate++ <--> DistanceChannel {  distance = 913km; } <--> ofs_Jacksonville.gate++;
        ofs_Jacksonville.gate++ <--> DistanceChannel {  distance = 525km; } <--> ofs_Miami.gate++;
        ofs_Jacksonville.gate++ <--> DistanceChannel {  distance = 458km; } <--> ofs_Atlanta.gate++;
        ofs_Atlanta.gate++ <--> DistanceChannel {  distance = 346km; } <--> ofs_Nashville.gate++;
        ofs_Atlanta.gate++ <--> DistanceChannel {  distance = 572km; } <--> ofs_Raleigh.gate++;
        ofs_Houston.gate++ <--> DistanceChannel {  distance = 569km; } <--> ofs_Jackson.gate++;
        ofs_Jackson.gate++ <--> DistanceChannel {  distance = 316km; } <--> ofs_Memphis.gate++;
        ofs_Memphis.gate++ <--> DistanceChannel {  distance = 306km; } <--> ofs_Nashville.gate++;
        ofs_Nashville.gate++ <--> DistanceChannel {  distance = 249km; } <--> ofs_Louisville.gate++;
        ofs_Louisville.gate++ <--> DistanceChannel {  distance = 172km; } <--> ofs_Indianapolis.gate++;
        ofs_Raleigh.gate++ <--> DistanceChannel {  distance = 375km; } <--> ofs_WashingtonDC.gate++;
        ofs_WashingtonDC.gate++ <--> DistanceChannel {  distance = 55km; } <--> ofs_Ashburn.gate++;
        ofs_WashingtonDC.gate++ <--> DistanceChannel {  distance = 199km; } <--> ofs_Philadelphia.gate++;
        ofs_Philadelphia.gate++ <--> DistanceChannel {  distance = 130km; } <--> ofs_NewYork.gate++;
        ofs_Chicago.gate++ <--> DistanceChannel {  distance = 497km; } <--> ofs_Cleveland.gate++;
        ofs_Cleveland.gate++ <--> DistanceChannel {  distance = 279km; } <--> ofs_Buffalo.gate++;
        ofs_Buffalo.gate++ <--> DistanceChannel {  distance = 644km; } <--> ofs_Boston.gate++;
        ofs_Cleveland.gate++ <--> DistanceChannel {  distance = 185km; } <--> ofs_Pittsburgh.gate++;
        ofs_Pittsburgh.gate++ <--> DistanceChannel {  distance = 360km; } <--> ofs_Ashburn.gate++;
        //        ofs_NewYork.gate++ <--> DistanceChannel {  distance = 84km; } <--> ofs_Bridgeport.gate++;
        //        ofs_Bridgeport.gate++ <--> DistanceChannel {  distance = 222km; } <--> ofs_Boston.gate++;
        ofs_NewYork.gate++ <--> DistanceChannel {  distance = 306km; } <--> ofs_Boston.gate++;
        ofs_Portland.gate++ <--> DistanceChannel {  distance = 907km; } <--> ofs_Sunnyvale.gate++;
        ofs_Sunnyvale.gate++ <--> DistanceChannel {  distance = 503km; } <--> ofs_LosAngeles.gate++;
        ofs_Sunnyvale.gate++ <--> DistanceChannel {  distance = 955km; } <--> ofs_SaltLakeCity.gate++;
        ofs_Denver.gate++ <--> DistanceChannel {  distance = 598km; } <--> ofs_SaltLakeCity.gate++;
        ofs_LosAngeles.gate++ <--> DistanceChannel {  distance = 934km; } <--> ofs_SaltLakeCity.gate++;
        ofs_Vancouver.gate++ <--> DistanceChannel {  distance = 194km; } <--> ofs_Seattle.gate++;
        ofs_Seattle.gate++ <--> DistanceChannel {  distance = 635km; } <--> ofs_Missoula.gate++;
        ofs_Seattle.gate++ <--> DistanceChannel {  distance = 233km; } <--> ofs_Portland.gate++;
        ofs_Seattle.gate++ <--> DistanceChannel {  distance = 1128km; } <--> ofs_SaltLakeCity.gate++;
        ofs_Vancouver.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Seattle.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Missoula.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Portland.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_SaltLakeCity.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Sunnyvale.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Denver.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_LosAngeles.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Phoenix.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Albuqerque.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_ElPaso.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Minneapolis.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_KansasCity.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Dallas.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Houston.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Chicago.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Indianapolis.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Louisville.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Nashville.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Memphis.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Jackson.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_BatonRouge.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Atlanta.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Jacksonville.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Raleigh.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Ashburn.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_WashingtonDC.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Cleveland.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Pittsburgh.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Buffalo.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Philadelphia.gate_controller++ <--> backboneline <--> controller.ethg++;
        //        ofs_Bridgeport.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Boston.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_Miami.gate_controller++ <--> backboneline <--> controller.ethg++;
        ofs_NewYork.gate_controller++ <--> backboneline <--> controller.ethg++;
}
