//
// Copyright (C) 2001 Monash University, Australia
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


package openflow.apps;

import inet.applications.contract.IPingApp;

//PingAppRandom:
// choses random destination node.
//
// PingApp:
//
// Generates ping requests and calculates the packet loss and round trip
// parameters of the replies.
//
// Start/stop time, interval etc can be specified via parameters. To disable,
// specify empty destAddr or stopTime<=startTime.
//
// Every ping request is sent out with a sequence number, and replies are
// expected to arrive in the same order. Whenever there's a jump in the
// in the received ping responses' sequence number (e.g. 1, 2, 3, 5), then
// the missing pings (number 4 in this example) is counted as lost.
// Then if it still arrives later (that is, a reply with a sequence number
// smaller than the largest one received so far) it will be counted as
// out-of-sequence arrival. So the number of really lost pings will be
// "lost" minus "out-of-order" (assuming there's no duplicate or bogus reply).
//
// Uses PingPayload as payload for the ICMP(v6) Echo Request/Reply packets.
//
// @see PingPayload, ICMP, ICMPv6Core
//
simple PingAppRandom like IPingApp
{
    parameters:
        string destAddr = default(""); // destination IP or IPv6 address
        string srcAddr = default(""); // source IP or IPv6 address (useful with multi-homing)
        double packetSize @unit("B") = default(56B); // of ping payload, in bytes
        volatile double sendInterval @unit("s") = default(1s); // time to wait between pings (can be random)
        double hopLimit = default(32); // TTL or hopLimit for IP packets
        double count = default(0); // stop after count ping requests, 0 means continuously
        double startTime @unit("s") = default(uniform(0s,this.interval)); // send first ping at startTime
        double stopTime @unit("s") = default(0s); // send no pings after stopTime, 0 means forever
        bool printPing = default(true); // dump on stdout
        string destinationNedType = default("inet.nodes.inet.StandardHost");
        @display("i=block/app");
        @signal[rtt](type=simtime_t);
        @signal[numLost](type=long);
        @signal[outOfOrderArrivals](type=long);
        @signal[pingTxSeq](type=long);
        @signal[pingRxSeq](type=long);
        @statistic[rtt](title="ping round-trip time"; unit=s; record=histogram,vector; interpolationmode=none);
        @statistic[numLost](title="pings lost"; record=last,vector; interpolationmode=none);
        @statistic[numOutOfOrderArrivals](title="ping out-of-order arrivals"; record=last,vector; interpolationmode=none);
        @statistic[pingTxSeq](title="ping tx seq"; record=count,vector; interpolationmode=none);
        @statistic[pingRxSeq](title="ping rx seq"; record=count,vector; interpolationmode=none);
    gates:
        input pingIn @labels(PingPayload/up);
        output pingOut @labels(PingPayload/down);
        input pingv6In @labels(PingPayload/up);
        output pingv6Out @labels(PingPayload/down);
}


