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

package openflow.ctrlApps;
// The Hub module doesn't contain any
//intelligence and just instructs the OpenFlow switch to 
//flood the packet on all ports
//(except the input port, where the packet arrived).
simple Hub like CtrlBehavior
{
    parameters:

        @display("i=block/fork");
    gates:

}
