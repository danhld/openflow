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

cplusplus {{
    #include "openflow.h"
    #include "Open_Flow_Message_m.h"
}};


packet Open_Flow_Message;


//Upon session establishment, the controller sends an OFP Features Request message
//to get information about the capabilities of a switch. This message does
//not contain a body beyond the OpenFlow header. The switch responds with an
//OFP Features Reply message.
packet OFP_Features_Request extends Open_Flow_Message
{
}