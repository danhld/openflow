An OpenFlow Extension for the OMNeT++ 5.1 with INET-3.6.0 Framework
=======
On this website, we present the implementation of our model of the OpenFlow system 
for INET-3.6.0 and OMNeT++ 5.1 based on the OpenFlow switch specification 1.0.

Required changes to the INET-3.6.0 framework
-------
The following changes are required so that the IPv4NetworkConfigurator ignores the data plane interfaces for
OpenFlow switches. The `EtherMACBase::registerInterface` method in `src/linklayer/ethernet/EtherMACBase` is changed 
so that the data plane interfaces of OpenFlow swtiches are not added to the InterfaceTable module and hence are ignored by the 
FlatNetworkConfigurator. 

ADD new parameter 

    bool doRegisterAtIft = default(true);

in the following modules:

* EtherMAC.ned
* EtherMACFullDuplex.ned

In class INET_API MACBase, add: 

bool doRegisterAtIft = true;

Modify class `src/inet/linklayer/base/MACBase`:
Add 
    bool doRegisterAtIft = true;
To the declaration of MACBase class

Change method `void MACBase::registerInterface() `

FROM

    if (ift)
        ift->addInterface(interfaceEntry);

TO

     if (ift && doRegisterAtIft){ 
	..
     }



Add 

doRegisterAtIft = par("doRegisterAtIft").boolValue();

To 

void EtherMACFullDuplex::initialize(int stage) and void EtherMAC::initialize(int stage):

void EtherMACFullDuplex::initialize(int stage)
{
    doRegisterAtIft = par("doRegisterAtIft").boolValue();
    EtherMACBase::initialize(stage);
.
.
.
}

void EtherMAC::initialize(int stage)
{
    doRegisterAtIft = par("doRegisterAtIft").boolValue();
    EtherMACBase::initialize(stage);
.
.
.
}


More informations about the implementation can be found on our webpage: [link](http://www3.informatik.uni-wuerzburg.de/research/ngn/ofomnet/of_omnet.shtml).
