Required changes to the INET framework:

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

Modify file src/linklayer/ethernet/EtherMACBase

IN

void EtherMACBase::registerInterface()

FROM

    if (ift)
        ift->addInterface(interfaceEntry);

TO

    if (ift && par("doRegisterAtIft").boolValue())
        ift->addInterface(interfaceEntry);

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		
EtherMAC.ned
EtherMACFullDuplex.ned

new parameter: bool doRegisterAtIft = default(true);

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

