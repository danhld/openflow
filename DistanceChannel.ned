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

package openflow;
import inet.common.misc.ThruputMeteringChannel;

// uses the geographical distance between two nodes and calculates the delay.
channel DistanceChannel extends ThruputMeteringChannel
{
  	double distance @unit(m) = default(0m);	
   	delay = this.distance / 200000km * 1s;
    datarate = 10Gbps;
    thruputDisplayFormat = "u";
}