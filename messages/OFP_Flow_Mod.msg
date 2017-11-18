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


struct oxm_basic_match;
struct ofp_action_output;
packet Open_Flow_Message;

// Modifications to a flow table by the controller.
packet OFP_Flow_Mod extends Open_Flow_Message
{
    
    
    
    uint64_t cookie; //* Opaque controller-issued identifier. */
    uint64_t cookie_mask; //* Mask used to restrict the cookie bits
                            //that must match when the command is
                            //OFPFC_MODIFY* or OFPFC_DELETE*. A value
                            //of 0 indicates no restriction. */
    //* Flow actions. */
    uint8_t table_id; //* ID of the table to put the flow in.
                            //For OFPFC_DELETE_* commands, OFPTT_ALL
                            //can also be used to delete matching
                            //flows from all tables. */
    uint8_t command; //* One of OFPFC_*. */
    uint16_t idle_timeout; //* Idle time before discarding (seconds). */
    uint16_t hard_timeout; //* Max time before discarding (seconds). */
    uint16_t priority; //* Priority level of flow entry. */
    uint32_t buffer_id; //* Buffered packet to apply to, or
                            //OFP_NO_BUFFER.
                            //Not meaningful for OFPFC_DELETE*. */
    uint32_t out_port; //* For OFPFC_DELETE* commands, require
                            //matching entries to include this as an
                            //output port. A value of OFPP_ANY
                            //indicates no restriction. */
    uint32_t out_group; //* For OFPFC_DELETE* commands, require
                            //matching entries to include this as an
                            //output group. A value of OFPG_ANY
                            //indicates no restriction. */
    uint16_t flags; //* One of OFPFF_*. */
    uint8_t pad[2];
    oxm_basic_match match; //* Fields to match. Variable size. */
    ofp_action_output actions[];
    //struct ofp_instruction instructions[0]; /* Instruction set */

}