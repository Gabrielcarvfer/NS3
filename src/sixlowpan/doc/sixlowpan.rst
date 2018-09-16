.. include:: replace.txt
.. highlight:: cpp


6LoWPAN: Transmission of IPv6 Packets over IEEE 802.15.4 Networks
-----------------------------------------------------------------

This chapter describes the implementation of |ns3| model for the
compression of IPv6 packets over IEEE 802.15.4-Based Networks 
as specified by :rfc:`4944` and :rfc:`6282`.

Model Description
*****************

The source code for the sixlowpan module lives in the directory ``src/sixlowpan``.

Design
======

The model design does not follow strictly the standard from an architectural 
standpoint, as it does extend it beyond the original scope by supporting also
other kinds of networks.

Other than that, the module strictly follows :rfc:`4944` and :rfc:`6282`, with the 
following exceptions:

* MESH and LOWPAN_BC0 dispatch types are not supported
* HC2 encoding is not supported
* IPHC's SAC and DAC are not supported

The MESH and LOWPAN_BC0 are not supported as they do apply only to mesh-under
architecture, which is not one of the goals of the module development.

The HC2 encoding is not supported, as it has been superseded by IPHC and NHC
compression type (\ :rfc:`6282`).

IPHC SAC and DAC are not yet supported, as they do require :rfc:`6775` for full 
compliance. It is planned to support them in the future. 

NetDevice
#########

The whole module is developed as a transparent NetDevice, which can act as a
proxy between IPv6 and any NetDevice (the module has been successfully tested 
with PointToPointNedevice, CsmaNetDevice and LrWpanNetDevice).

For this reason, the module implements a virtual NetDevice, and all the calls are passed
without modifications to the underlying NetDevice. The only important difference is in
GetMtu behaviour. It will always return *at least* 1280 bytes, as is the minimum IPv6 MTU.

The module does provide some attributes and some tracesources.
The attributes are:

* Rfc6282 (boolean, default true), used to activate HC1 (:rfc:`4944`) or IPHC (:rfc:`6282`) compression.
* OmitUdpChecksum (boolean, default true), used to activate UDP checksum compression in IPHC.
* FragmentReassemblyListSize (integer, default 0), indicating the number of packets that can be reassembled at the same time. If the limit is reached, the oldest packet is discarded. Zero means infinite.
* FragmentExpirationTimeout (Time, default 60 seconds), being the timeout to wait for further fragments before discarding a partial packet.
* CompressionThreshold (unsigned 32 bits integer, default 0), minimum compressed payload size. 
* ForceEtherType (boolean, default false), and
* EtherType (unsigned 16 bits integer, default 0xFFFF), to force a particular L2 EtherType.

The CompressionThreshold attribute is similar to Contiki's SICSLOWPAN_CONF_MIN_MAC_PAYLOAD
option. If a compressed packet size is less than the threshold, the uncompressed version is
used (plus one byte for the correct dispatch header).
This option is useful when a MAC requires a minimum frame size (e.g., ContikiMAC) and the 
compression would violate the requirement.

The last two attributes are needed to use the module with a NetDevice other than 802.15.4, as
neither IANA or IEEE did reserve an EtherType for 6LoWPAN. As a consequence there might be a
conflict with the L2 multiplexer/demultiplexer which is based on EtherType. The default 
value is 0xFFFF, which is reserved by IEEE (see [IANA802]_ and [Ethertype]_).
The default module behaviour is to not change the EtherType, however this would not work with
any NetDevice actually understanding and using the EtherType.

Note that the `ForceEtherType` parameter have also a direct effect on the MAC address kind the
module is expecting to handle:
* ForceEtherType true: Mac48Address (Ethernet, WiFi, etc.).
* ForceEtherType false: Mac16Address or Mac64Address (IEEE 802.15.4).

Note that using 6LoWPAN over any NetDevice other than 802.15.4 will produce valid .pcap files,
but they will not be correctly dissected by Wireshark.
The reason lies on the fact that 6LoWPAN was really meant to be used only over 802.15.4, so
Wireshark dissectors will not even try to decode 6LoWPAN headers on top of protocols other than
802.15.4.

The Trace sources are:

* Tx - exposing packet (including 6LoWPAN header), SixLoWPanNetDevice Ptr, interface index.
* Rx - exposing packet (including 6LoWPAN header), SixLoWPanNetDevice Ptr, interface index.
* Drop - exposing DropReason, packet (including 6LoWPAN header), SixLoWPanNetDevice Ptr, interface index.

The Tx and Rx traces are called as soon as a packet is received or sent. The Drop trace is
invoked when a packet (or a fragment) is discarded.


Scope and Limitations
=====================

Future versions of this module will support :rfc:`6775`, however no timeframe is guaranteed.

Using 6LoWPAN with IPv4 (or other L3 protocols)
###############################################

As the name implies, 6LoWPAN can handle only IPv6 packets. Any other protocol will be discarded.
Moreover, 6LoWPAN assumes that the network is uniform, as is all the devices connected by the
same same channel are using 6LoWPAN. Mixed environments are not supported by the standard.
The reason is simple: 802.15.4 frame doesn't have a "protocol" field. As a consequence,
there is no demultiplexing at MAC layer and the protocol carried by L2 frames must be known
in advance.

In the |ns3| implementation it is possible, but not advisable, to violate this requirement
if the underlying NetDevice is capable of discriminating different protocols. As an example,
CsmaNetDevice can carry IPv4 and 6LoWPAN at the same time. However, this configuration has 
not been tested.

References
==========

.. [RFC4944] :rfc:`4944`, "Transmission of IPv6 Packets over IEEE 802.15.4 Networks"
.. [RFC6282] :rfc:`6282`, "Compression Format for IPv6 Datagrams over IEEE 802.15.4-Based Networks"
.. [RFC6775] :rfc:`6775`, "Neighbor Discovery Optimization for IPv6 over Low-Power Wireless Personal Area Networks (6LoWPANs)"
.. [IANA802] IANA, assigned IEEE 802 numbers: http://www.iana.org/assignments/ieee-802-numbers/ieee-802-numbers.xml
.. [Ethertype] IEEE Ethertype numbers: http://standards.ieee.org/develop/regauth/ethertype/eth.txt

Usage
*****

Enabling sixlowpan
==================

Add ``sixlowpan`` to the list of modules built with |ns3|.

Helper
======

The helper is patterned after other device helpers. 

Examples
========

The following example can be found in ``src/sixlowpan/examples/``:

* ``example-sixlowpan.cc``:  A simple example showing end-to-end data transfer.

In particular, the example enables a very simplified end-to-end data
transfer scenario, with a CSMA network forced to carry 6LoWPAN compressed packets.


Tests
=====

The test provided checks the connection between two UDP clients and the correctness of the received packets.

Validation
**********

The model has been validated against WireShark, checking whatever the packets are correctly
interpreted and validated.


