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
    #include "inet/linklayer/ethernet/EtherFrame_m.h"
    
    inline std::ostream& operator<<(std::ostream& os, ofp_action_output action)
    {
		os << "Port (hex): " << std::hex << action.port << endl;
		return os;
	}
}};

//struct ofp_action_header;
struct ofp_action_output;
class EthernetIIFrame;
packet Open_Flow_Message;

//When the controller decides to send a packet out through the data plane, it uses the
//OFP PACKET OUT message.
packet OFP_Packet_Out extends Open_Flow_Message
{
	uint32_t buffer_id; // ID assigned by datapath (OFP_NO_BUFFER
                        //if none). 
	uint32_t in_port; // Packet�s input port or OFPP_CONTROLLER. 
	
	 ofp_action_output actions[]; // Action list. 
//	 EthernetIIFrame frame;
	 uint8_t data[0];   // Packet data. The length is inferred
							//from the length field in the header.
							//(Only meaningful if buffer_id == -1.) 
}