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

package openflow.utility;

// Calculates the distances between
//the controller and all OpenFlow switches in a single controller scenario.
// Location is specified with the index of an OpenFlow domain.
simple placeController
{
    parameters:
        int location_index = default(-1);
        string domainNedType = default("openflow.nodes.OpenFlow_Domain");
        @display("i=block/broadcast");
}
