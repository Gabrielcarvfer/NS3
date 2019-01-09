/* etypes.h
 * Defines ethernet packet types, similar to tcpdump's ethertype.h
 *
 * $Id: etypes.h 3992 2008-06-10 03:13:11Z dgu $
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __ETYPES_H__
#define __ETYPES_H__

/*
 * Maximum length of an IEEE 802.3 frame; Ethernet type/length values
 * greater than it are types, Ethernet type/length values less than or
 * equal to it are lengths.
 */
#define IEEE_802_3_MAX_LEN 1500

#ifndef ETHERTYPE_UNK
#define ETHERTYPE_UNK		0x0000
#endif

/* Sources:
 * http://www.iana.org/assignments/ethernet-numbers
 * TCP/IP Illustrated, Volume 1
 * RFCs 894, 1042, 826
 * tcpdump's ethertype.h
 * http://www.cavebear.com/CaveBear/Ethernet/
 * http://standards.ieee.org/regauth/ethertype/type-pub.html
 * http://standards.ieee.org/regauth/ethertype/eth.txt
 * (The first of the two IEEE URLs is the one that the "EtherType Field
 * Public Assignments" link on the page at
 *
 *	http://standards.ieee.org/regauth/ethertype/index.shtml
 *
 * goes to, but it is redirected to the second of those - i.e., both
 * of the IEEE URLs ultimately go to the same page.)
 */

/* Order these values by number */

#ifndef ETHERTYPE_XNS_IDP
#define ETHERTYPE_XNS_IDP	0x0600
#endif

#ifndef ETHERTYPE_IP
#define ETHERTYPE_IP		0x0800
#endif

#ifndef ETHERTYPE_X25L3
#define ETHERTYPE_X25L3		0x0805
#endif

#ifndef ETHERTYPE_ARP
#define ETHERTYPE_ARP		0x0806
#endif

#ifndef ETHERTYPE_WOL
#define ETHERTYPE_WOL		0x0842 /* Wake on LAN.  Not offically registered. */
#endif

#ifndef ETHERTYPE_WMX_M2M
#define ETHERTYPE_WMX_M2M	0x08f0
#endif

#ifndef ETHERTYPE_VINES_IP
#define ETHERTYPE_VINES_IP	0x0bad
#endif

#ifndef ETHERTYPE_VINES_ECHO
#define ETHERTYPE_VINES_ECHO	0x0baf
#endif

#ifndef ETHERTYPE_TRAIN
/*
 * Created by Microsoft Network Monitor as a summary packet.
 */
#define ETHERTYPE_TRAIN		0x1984
#endif

#ifndef ETHERTYPE_CGMP
#define ETHERTYPE_CGMP		0x2001
#endif

#ifndef ETHERTYPE_CENTRINO_PROMISC
#define ETHERTYPE_CENTRINO_PROMISC	0x2452	/* Intel Centrino promiscuous packets */
#endif

#ifndef ETHERTYPE_3C_NBP_DGRAM
#define ETHERTYPE_3C_NBP_DGRAM	0x3c07
#endif

#ifndef ETHERTYPE_EPL_V1
#define ETHERTYPE_EPL_V1	0x3E3F
#endif

#ifndef ETHERTYPE_DEC
#define ETHERTYPE_DEC		0x6000
#endif

#ifndef ETHERTYPE_DNA_DL
#define ETHERTYPE_DNA_DL	0x6001
#endif

#ifndef ETHERTYPE_DNA_RC
#define ETHERTYPE_DNA_RC	0x6002
#endif

#ifndef ETHERTYPE_DNA_RT
#define ETHERTYPE_DNA_RT	0x6003
#endif

#ifndef ETHERTYPE_LAT
#define ETHERTYPE_LAT		0x6004
#endif

#ifndef ETHERTYPE_DEC_DIAG
#define ETHERTYPE_DEC_DIAG	0x6005
#endif

#ifndef ETHERTYPE_DEC_CUST
#define ETHERTYPE_DEC_CUST	0x6006
#endif

#ifndef ETHERTYPE_DEC_SCA
#define ETHERTYPE_DEC_SCA	0x6007
#endif

#ifndef ETHERTYPE_ETHBRIDGE
#define ETHERTYPE_ETHBRIDGE	0x6558	/* transparent Ethernet bridging [RFC1701]*/
#endif

#ifndef ETHERTYPE_RAW_FR
#define ETHERTYPE_RAW_FR	0x6559	/* Raw Frame Relay        [RFC1701] */
#endif

#ifndef ETHERTYPE_REVARP
#define ETHERTYPE_REVARP	0x8035
#endif

#ifndef ETHERTYPE_DEC_LB
#define ETHERTYPE_DEC_LB	0x8038
#endif

#ifndef ETHERTYPE_DEC_LAST
#define ETHERTYPE_DEC_LAST	0x8041	/* DEC Local Area Systems Transport */
#endif

#ifndef ETHERTYPE_ATALK
#define ETHERTYPE_ATALK		0x809b
#endif

#ifndef ETHERTYPE_SNA
#define ETHERTYPE_SNA		0x80d5
#endif

#ifndef ETHERTYPE_AARP
#define ETHERTYPE_AARP		0x80f3
#endif

#ifndef ETHERTYPE_VLAN
#define ETHERTYPE_VLAN		0x8100	/* 802.1Q Virtual LAN */
#endif

#ifndef ETHERTYPE_NSRP
#define ETHERTYPE_NSRP		0x8133
#endif

#ifndef ETHERTYPE_IPX
#define ETHERTYPE_IPX		0x8137
#endif

#ifndef ETHERTYPE_SNMP
#define ETHERTYPE_SNMP		0x814c	/* SNMP over Ethernet, RFC 1089 */
#endif

#ifndef ETHERTYPE_WCP
#define ETHERTYPE_WCP		0x80ff	/* Wellfleet Compression Protocol */
#endif

#ifndef ETHERTYPE_STP
#define ETHERTYPE_STP		0x8181	/* STP, HIPPI-ST */
#endif

#ifndef ETHERTYPE_ISMP
#define ETHERTYPE_ISMP		0x81fd	/* Cabletron Interswitch Message Protocol */
#endif

#ifndef ETHERTYPE_ISMP_TBFLOOD
#define ETHERTYPE_ISMP_TBFLOOD	0x81ff	/* Cabletron Interswitch Message Protocol */
#endif

#ifndef ETHERTYPE_IPv6
#define ETHERTYPE_IPv6		0x86dd
#endif

#ifndef ETHERTYPE_WLCCP
#define ETHERTYPE_WLCCP		0x872d	/* Cisco Wireless Lan Context Control Protocol */
#endif

#ifndef ETHERTYPE_MAC_CONTROL
#define ETHERTYPE_MAC_CONTROL	0x8808
#endif

#ifndef ETHERTYPE_SLOW_PROTOCOLS
#define ETHERTYPE_SLOW_PROTOCOLS	0x8809
#endif

#ifndef ETHERTYPE_PPP
#define ETHERTYPE_PPP		0x880b	/* no, this is not PPPoE */
#endif

#ifndef ETHERTYPE_COBRANET
#define ETHERTYPE_COBRANET	0x8819	/* Cirrus cobranet */
#endif

#ifndef ETHERTYPE_MPLS
#define ETHERTYPE_MPLS		0x8847	/* MPLS unicast packet */
#endif

#ifndef ETHERTYPE_MPLS_MULTI
#define ETHERTYPE_MPLS_MULTI	0x8848	/* MPLS multicast packet */
#endif

#ifndef ETHERTYPE_FOUNDRY
#define ETHERTYPE_FOUNDRY	0x885a	/* Some Foundry proprietary protocol */
#endif

#ifndef ETHERTYPE_PPPOED
#define ETHERTYPE_PPPOED	0x8863	/* PPPoE Discovery Protocol */
#endif

#ifndef ETHERTYPE_PPPOES
#define ETHERTYPE_PPPOES	0x8864	/* PPPoE Session Protocol */
#endif

#ifndef ETHERTYPE_INTEL_ANS
#define ETHERTYPE_INTEL_ANS	0x886d	/* Intel ANS (NIC teaming) http://www.intel.com/support/network/adapter/ans/probes.htm */
#endif

#ifndef ETHERTYPE_MS_NLB_HEARTBEAT
#define ETHERTYPE_MS_NLB_HEARTBEAT	0x886f	/* MS Network Load Balancing heartbeat http://www.microsoft.com/technet/treeview/default.asp?url=/TechNet/prodtechnol/windows2000serv/deploy/confeat/nlbovw.asp */
#endif

#ifndef ETHERTYPE_HOMEPLUG
#define ETHERTYPE_HOMEPLUG    0x887B  /* IEEE assigned Ethertype */
#endif

#ifndef ETHERTYPE_CDMA2000_A10_UBS
#define ETHERTYPE_CDMA2000_A10_UBS	0x8881	/* the byte stream protocol that is used for IP based micro-mobility bearer interfaces (A10) in CDMA2000(R)-based wireless networks */
#endif

#ifndef ETHERTYPE_EAPOL
#define ETHERTYPE_EAPOL 	0x888e  /* 802.1x Authentication */
#endif

#ifndef ETHERTYPE_PROFINET
#define ETHERTYPE_PROFINET 	0x8892  /* PROFIBUS PROFINET protocol */
#endif

#ifndef ETHERTYPE_HYPERSCSI
#define ETHERTYPE_HYPERSCSI     0x889A  /* HyperSCSI */
#endif

#ifndef ETHERTYPE_CSM_ENCAPS
#define ETHERTYPE_CSM_ENCAPS	0x889B /* Mindspeed Technologies www.mindspeed.com */
#endif

#ifndef ETHERTYPE_TELKONET
#define ETHERTYPE_TELKONET	0x88A1 /* Telkonet powerline ethernet */
#endif

#ifndef ETHERTYPE_AOE
#define ETHERTYPE_AOE           0x88A2
#endif

#ifndef ETHERTYPE_ECATF
#define ETHERTYPE_ECATF 0x88A4 /* Ethernet type for EtherCAT frames */
#endif

#ifndef ETHERTYPE_IEEE_802_1AD
#define ETHERTYPE_IEEE_802_1AD  0x88A8 /* IEEE 802.1ad Provider Bridge, Q-in-Q */
#endif

#ifndef ETHERTYPE_EPL_V2
#define ETHERTYPE_EPL_V2        0x88AB
#endif

#ifndef ETHERTYPE_BRDWALK
#define ETHERTYPE_BRDWALK       0x88AE
#endif

#ifndef ETHERTYPE_IEEE802_OUI_EXTENDED
#define ETHERTYPE_IEEE802_OUI_EXTENDED 0x88B7	/* IEEE 802a OUI Extended Ethertype */
#endif

#ifndef ETHERTYPE_IEC61850_GOOSE
#define ETHERTYPE_IEC61850_GOOSE	0x88b8  /* IEC 61850 is a global standard for the use in utility communication,*/
#endif						/* in particular for the information exchange between IED's in a power */
						/* transmission or distribution substation. */
						/*  There are three types of application services
						    that use a specific EtherType. GOOSE uses
						    EtherType field 88b8, GSE management services
						    uses EtherType field 88b9. These two protocols
						    are defined in IEC 61850-8-1. SV (Sampled
						    Value Transmission) uses EtherType field
						    88ba; the protocol is defined in IEC 61850-9-1
						    and IEC 61850-9-2. */

#ifndef ETHERTYPE_IEC61850_GSE
#define ETHERTYPE_IEC61850_GSE		0x88b9  /* IEC 61850 is a global standard for the use in utility communication,*/
#endif						/* in particular for the information exchange between IED's in a power */

#ifndef ETHERTYPE_IEC61850_SV
#define ETHERTYPE_IEC61850_SV		0x88ba	/* IEC 61850 is a global standard for the use in utility communication,*/
#endif						/* in particular for the information exchange between IED's in a power */

#ifndef ETHERTYPE_TIPC
#define ETHERTYPE_TIPC	0x88ca  /* TIPC  (Transparent Inter Process Communication, */
#endif				/* http://tipc.sourceforge.net/) Ericsson Research Canada Inc */

#ifndef ETHERTYPE_RSN_PREAUTH
#define ETHERTYPE_RSN_PREAUTH	0x88c7  /* 802.11i Pre-Authentication */
#endif

#ifndef ETHERTYPE_LLDP
#define ETHERTYPE_LLDP	        0x88cc  /* IEEE 802.1AB Link Layer Discovery Protocol (LLDP) */
#endif

#ifndef ETHERTYPE_SERCOS
#define ETHERTYPE_SERCOS        0x88cd  /* SERCOS interface real-time protocol for motion control */
#endif

#ifndef ETHERTYPE_3GPP2
#define ETHERTYPE_3GPP2	        0x88d2  /* This will be used in a revision of the Interoperabi */
#endif					/* Specification (IOS) for cdma2000 Access Network Interfaces (document numbers A.S0011-B */
					/* through A.S0017-B v1.0). This document already uses the Ether type 8881 */

#ifndef ETHERTYPE_LLTD
#define ETHERTYPE_LLTD		0x88d9  /* Link Layer Topology Discovery (LLTD) */
#endif

#ifndef ETHERTYPE_MRP
#define ETHERTYPE_MRP	        0x88e3  /* IEC 61158-6-10 Media Redundancy Protocol (MRP) */
#endif

#ifndef ETHERTYPE_IEEE_802_1AH
#define ETHERTYPE_IEEE_802_1AH  0x88F0 /* IEEE 802.1ah Provider Backbone Bridge Mac-in-Mac */
#endif

#ifndef ETHERTYPE_PTP
#define ETHERTYPE_PTP		0x88F7	/* IEEE1588v2 (PTPv2) over Ethernet */
#endif					/* in particular for the information exchange between IED's in a power */
					/* transmission or distribution substation. */
					/*  There are three types of application services */

#ifndef ETHERTYPE_PRP
#define ETHERTYPE_PRP		0x88FB	/* Parallel Redundancy Protocol (IEC62439 Chapter 6) */
#endif

#ifndef ETHERTYPE_CFM
#define ETHERTYPE_CFM		0x8902	/* IEEE 802.1ag Connectivity Fault Management */
#endif								/* (CFM) protocol. */

#ifndef ETHERTYPE_FCOE
#define ETHERTYPE_FCOE		0x8906	/* Fibre Channel over Ethernet */
#endif

#ifndef ETHERTYPE_LOOP
#define ETHERTYPE_LOOP		0x9000 	/* used for layer 2 testing (do i see my own frames on the wire) */
#endif

#ifndef ETHERTYPE_RTMAC
#define ETHERTYPE_RTMAC		0x9021 	/* RTnet: Real-Time Media Access Control */
#endif

#ifndef ETHERTYPE_RTCFG
#define ETHERTYPE_RTCFG		0x9022 	/* RTnet: Real-Time Configuration Protocol */
#endif

#ifndef ETHERTYPE_LLT
#define ETHERTYPE_LLT           0xCAFE /* Veritas Low Latency Transport (not officially registered) */
#endif

#ifndef ETHERTYPE_FCFT
/* type used to transport FC frames+MDS hdr internal to Cisco's MDS switch */
#define ETHERTYPE_FCFT          0xFCFC
#endif

extern const value_string etype_vals[];

#endif /* etypes.h */
