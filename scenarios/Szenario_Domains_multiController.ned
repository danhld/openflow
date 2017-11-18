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
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;

import openflow.nodes.*;
import openflow.DistanceChannel;
import openflow.utility.SpanningTree;

network MultiController
{
    @display("bgb=842,642;bgi=maps/usa");


    submodules:
        configurator: FlatNetworkConfigurator {
            parameters:
                @display("p=590,83;is=n");
        }

        //		0
        Vancouver: Domain_wController {
            @display("p=108,10");
        }
        //		1
        Seattle: Domain_wController {
            @display("p=78,49");
        }

        //		2
        Portland: Domain_wController {
            @display("p=69,88");
        }

        //		3
        Sunnyvale: Domain_wController {
            @display("p=39,254");
        }

        //		4
        LosAngeles: Domain_wController {
            @display("p=66,287");
        }

        //		5
        Missoula: Domain_wController {
            @display("p=187,88");
        }

        //		6
        SaltLakeCity: Domain_wController {
            @display("p=168,207");
        }

        //		7
        Phoenix: Domain_wController {
            @display("p=150,314");
        }

        //		8
        Denver: Domain_wController {
            @display("p=250,234");
        }

        //		9
        Albuqerque: Domain_wController {
            @display("p=230,293");
        }

        //		10
        ElPaso: Domain_wController {
            @display("p=257,363");
        }

        //		11
        Minneapolis: Domain_wController {
            @display("p=415,135");
        }

        //		12
        KansasCity: Domain_wController {
            @display("p=396,246");
        }

        //		13
        Dallas: Domain_wController {
            @display("p=376,347");
        }

        //		14
        Houston: Domain_wController {
            @display("p=415,404");
        }

        //		15
        Chicago: Domain_wController {
            @display("p=483,184");
        }

        //		16
        Indianapolis: Domain_wController {
            @display("p=522,223");
        }

        //		17
        Louisville: Domain_wController {
            @display("p=528,254");
        }

        //		18
        Nashville: Domain_wController {
            @display("p=504,301");
        }
        //		19
        Memphis: Domain_wController {
            @display("p=465,314");
        }
        //		20
        Jackson: Domain_wController {
            @display("p=465,363");
        }

        //		21
        BatonRouge: Domain_wController {
            @display("p=468,390");
        }

        //		22
        Cleveland: Domain_wController {
            @display("p=576,174");
        }

        //		23
        Pittsburgh: Domain_wController {
            @display("p=600,196");
        }
        //		24
        Atlanta: Domain_wController {
            @display("p=549,332");
        }
        //		25
        Jacksonville: Domain_wController {
            @display("p=600,378");
        }
        //		26
        Buffalo: Domain_wController {
            @display("p=607,156");
        }
        //		27
        Ashburn: Domain_wController {
            @display("p=627,214");
        }
        //		28
        Raleigh: Domain_wController {
            @display("p=622,285");
        }

        //		29
        WashingtonDC: Domain_wController {
            @display("p=654,229");
        }

        //		30
        Miami: Domain_wController {
            @display("p=632,443");
        }
        //		31
        Philadelphia: Domain_wController {
            @display("p=659,189");
        }
        //		32
        NewYork: Domain_wController {
            @display("p=684,169");
        }
        //		33
//        Bridgeport: Domain_wController {
//            @display("p=706,162");
//        }

        //		34
        Boston: Domain_wController {
            @display("p=720,135");
        }

        spanningTree: SpanningTree {
            @display("p=499,460");
        }

    connections allowunconnected:

        LosAngeles.gate++ <--> DistanceChannel {  distance = 575km; } <--> Phoenix.gate++;
        Phoenix.gate++ <--> DistanceChannel {  distance = 557km; } <--> ElPaso.gate++;
        ElPaso.gate++ <--> DistanceChannel {  distance = 369km; } <--> Albuqerque.gate++;
        ElPaso.gate++ <--> DistanceChannel {  distance = 1087km; } <--> Houston.gate++;
        Albuqerque.gate++ <--> DistanceChannel {  distance = 537km; } <--> Denver.gate++;
        Denver.gate++ <--> DistanceChannel {  distance = 898km; } <--> KansasCity.gate++;
        Missoula.gate++ <--> DistanceChannel {  distance = 1617km; } <--> Minneapolis.gate++;
        Minneapolis.gate++ <--> DistanceChannel {  distance = 572km; } <--> Chicago.gate++;
        Houston.gate++ <--> DistanceChannel {  distance = 362km; } <--> Dallas.gate++;
        Dallas.gate++ <--> DistanceChannel {  distance = 729km; } <--> KansasCity.gate++;
        KansasCity.gate++ <--> DistanceChannel {  distance = 662km; } <--> Chicago.gate++;
        Chicago.gate++ <--> DistanceChannel {  distance = 263km; } <--> Indianapolis.gate++;
        Houston.gate++ <--> DistanceChannel {  distance = 413km; } <--> BatonRouge.gate++;
        BatonRouge.gate++ <--> DistanceChannel {  distance = 913km; } <--> Jacksonville.gate++;
        Jacksonville.gate++ <--> DistanceChannel {  distance = 525km; } <--> Miami.gate++;
        Jacksonville.gate++ <--> DistanceChannel {  distance = 458km; } <--> Atlanta.gate++;
        Atlanta.gate++ <--> DistanceChannel {  distance = 346km; } <--> Nashville.gate++;
        Atlanta.gate++ <--> DistanceChannel {  distance = 572km; } <--> Raleigh.gate++;
        Houston.gate++ <--> DistanceChannel {  distance = 569km; } <--> Jackson.gate++;
        Jackson.gate++ <--> DistanceChannel {  distance = 316km; } <--> Memphis.gate++;
        Memphis.gate++ <--> DistanceChannel {  distance = 306km; } <--> Nashville.gate++;
        Nashville.gate++ <--> DistanceChannel {  distance = 249km; } <--> Louisville.gate++;
        Louisville.gate++ <--> DistanceChannel {  distance = 172km; } <--> Indianapolis.gate++;
        Raleigh.gate++ <--> DistanceChannel {  distance = 375km; } <--> WashingtonDC.gate++;
        WashingtonDC.gate++ <--> DistanceChannel {  distance = 55km; } <--> Ashburn.gate++;
        WashingtonDC.gate++ <--> DistanceChannel {  distance = 199km; } <--> Philadelphia.gate++;
        Philadelphia.gate++ <--> DistanceChannel {  distance = 130km; } <--> NewYork.gate++;
        Chicago.gate++ <--> DistanceChannel {  distance = 497km; } <--> Cleveland.gate++;
        Cleveland.gate++ <--> DistanceChannel {  distance = 279km; } <--> Buffalo.gate++;
        Buffalo.gate++ <--> DistanceChannel {  distance = 644km; } <--> Boston.gate++;
        Cleveland.gate++ <--> DistanceChannel {  distance = 185km; } <--> Pittsburgh.gate++;
        Pittsburgh.gate++ <--> DistanceChannel {  distance = 360km; } <--> Ashburn.gate++;
        //        NewYork.gate++ <--> DistanceChannel {  distance = 84km; } <--> Bridgeport.gate++;
        //        Bridgeport.gate++ <--> DistanceChannel {  distance = 222km; } <--> Boston.gate++;
        NewYork.gate++ <--> DistanceChannel {  distance = 306km; } <--> Boston.gate++;
        Portland.gate++ <--> DistanceChannel {  distance = 907km; } <--> Sunnyvale.gate++;
        Sunnyvale.gate++ <--> DistanceChannel {  distance = 503km; } <--> LosAngeles.gate++;
        Sunnyvale.gate++ <--> DistanceChannel {  distance = 955km; } <--> SaltLakeCity.gate++;
        Denver.gate++ <--> DistanceChannel {  distance = 598km; } <--> SaltLakeCity.gate++;
        LosAngeles.gate++ <--> DistanceChannel {  distance = 934km; } <--> SaltLakeCity.gate++;
        Vancouver.gate++ <--> DistanceChannel {  distance = 194km; } <--> Seattle.gate++;
        Seattle.gate++ <--> DistanceChannel {  distance = 635km; } <--> Missoula.gate++;
        Seattle.gate++ <--> DistanceChannel {  distance = 233km; } <--> Portland.gate++;
        Seattle.gate++ <--> DistanceChannel {  distance = 1128km; } <--> SaltLakeCity.gate++;
}
