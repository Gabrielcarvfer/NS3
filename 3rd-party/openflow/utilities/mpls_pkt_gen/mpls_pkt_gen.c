#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<features.h>
#include<linux/if_packet.h>
#include<linux/if_ether.h>
#include<errno.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include"csum.h"

#define PACKET_LENGTH	1024

#define ETH_TYPE_IP		0x0800
#define ETH_TYPE_MPLS_UNICAST	0x8847

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef union
{
	struct
	{
	 #if BYTE_ORDER == BIG_ENDIAN
	 uint32_t	label:20;
	 uint8_t 	exp:3;
	 uint8_t  	s:1;
	 uint8_t  	ttl:8;
	#else
	 uint8_t   	ttl:8;
	 uint8_t   	s:1;
	 uint8_t   	exp:3;
	 uint32_t	label:20;
	#endif
	};
	uint32_t value;
} mpls_header;

int CreateRawSocket(int protocol_to_sniff)
{
	int rawsock;

	if((rawsock = socket(PF_PACKET, SOCK_RAW, htons(protocol_to_sniff)))== -1)
	{
		perror("Error creating raw socket: ");
		exit(-1);
	}

	return rawsock;
}

int BindRawSocketToInterface(char *device, int rawsock, int protocol)
{
	
	struct sockaddr_ll sll;
	struct ifreq ifr;

	bzero(&sll, sizeof(sll));
	bzero(&ifr, sizeof(ifr));
	
	/* First Get the Interface Index  */


	strncpy((char *)ifr.ifr_name, device, IFNAMSIZ);
	if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
	{
		printf("Error getting Interface index !\n");
		exit(-1);
	}

	/* Bind our raw socket to this interface */

	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = ifr.ifr_ifindex;
	sll.sll_protocol = htons(protocol); 


	if((bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)))== -1)
	{
		perror("Error binding raw socket to interface\n");
		exit(-1);
	}

	return 1;
	
}


int SendRawPacket(int rawsock, unsigned char *pkt, int pkt_len)
{
	int sent= 0;

	/* A simple write on the socket ..thats all it takes ! */

	if((sent = write(rawsock, pkt, pkt_len)) != pkt_len)
	{
		return 0;
	}

	return 1;
	

}

   #define ETH_DST_ADDR 	 0
   #define ETH_SRC_ADDR 	 ETH_DST_ADDR+ETH_ALEN
   #define ETH_TYPE_ADDR	 ETH_SRC_ADDR+ETH_ALEN
   #define MPLS_HDR_ADDR	 ETH_TYPE_ADDR+2
   #define IP_HDR_ADDR 		 MPLS_HDR_ADDR+4

void write_ethernet_header(unsigned char *packet, unsigned short eth_type)
{
  /*our MAC address*/
  unsigned char src_mac[6] = {0x00, 0x1a, 0x4b, 0x53, 0xf7, 0x2c};
  
  /*other host MAC address*/
  //unsigned char dest_mac[6] = {0x00, 0x1a, 0x4b, 0x53, 0xf7, 0x2d};
  unsigned char dest_mac[6] = {0x00, 0x1a, 0x4b, 0x53, 0xf7, 0x2c};


  //unsigned char eth_type[2] = {0x88, 0x47};
  eth_type = htons(eth_type);

  memcpy((void*)(packet+ETH_DST_ADDR), (void*)dest_mac, ETH_ALEN);
  memcpy((void*)(packet+ETH_SRC_ADDR), (void*)src_mac, ETH_ALEN);
  memcpy((void*)(packet+ETH_TYPE_ADDR), (void*)&eth_type, 2);

 

}


void write_mpls_header(unsigned char *packet, unsigned int label, unsigned int exp, unsigned int s, unsigned int ttl)
{
  mpls_header mpls_header1;

  mpls_header1.ttl = ttl;
  mpls_header1.exp = exp;
  mpls_header1.s = s;
  mpls_header1.label = label;


  //printf("mpls_header1 = %x\n", mpls_header1.value);
  //printf("mpls_header1.label = %u\n"
  //       "mpls_header1.CoS = %u\n"
  //       "mpls_header1.s = %u\n"
  //       "mpls_header1.TTL = %u\n",
         //mpls_header1.label, mpls_header1.exp, mpls_header1.s, mpls_header1.ttl);

  uint32_t mpls_wire = htonl(mpls_header1.value);

  memcpy((void*)(packet), (void *) &mpls_wire, 4);
}

void write_ip_header(unsigned char *packet, unsigned short ip_pkt_len)
{

//  unsigned short ip_pkt_len = PACKET_LENGTH - (IP_HDR_ADDR);
  unsigned char ip_hdr[20] = { 0x45, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00,
                               0xFF, 0x11, 0xa3, 0xfc,
                               0x0a, 0x00, 0x00, 0x02, 
                               0x0a, 0x00, 0x00, 0x01};

  ip_hdr[2] = (0xFF00 & ip_pkt_len) >> 8;
  ip_hdr[3] = 0x00FF & ip_pkt_len;

  memcpy((void *)(packet), (void *) &ip_hdr, 20);

}

void write_udp_header(unsigned char *packet, unsigned short udp_len)
{
//  unsigned short udp_len = PACKET_LENGTH - (IP_HDR_ADDR) - 20;
  unsigned char udp_hdr[8] = {0x0F, 0x00, 0x0F, 0x00,
                              0x00, 0x00, 0x00, 0x00};
  
  udp_hdr[4] = (0xFF00 & udp_len) >> 8;
  udp_hdr[5] = (0x00FF & udp_len);


  //printf("udp_len = %u   udp_hdr[4]=%02x udp_hdr[5]=%02x\n", udp_len
///         ,udp_hdr[4], udp_hdr[5]);


  memcpy((void *)(packet), (void *) &udp_hdr, 8);

}

void write_ip_csum(unsigned char *packet, unsigned short len)
{
  // len should be just the length of the header
  unsigned short ip_csum = 0;
  // initialize the ip checksum field to 0 for 
  // purposes of calculating the header
  memcpy(packet + 10, &ip_csum, 2);

  // appears to return in network byte order somehow
  ip_csum = csum(packet, len);
  memcpy(packet + 10, &ip_csum, 2);
}


/* argv[1] is the device e.g. eth0
   argv[2] is the number of packets to send
*/
 
main(int argc, char **argv)
{

	int raw;
	unsigned char packet[PACKET_LENGTH];
	unsigned char *packet_pos = packet;
	unsigned char *ip_pos;
	char scanfstr[1024];
	unsigned int label, exp, ttl;
	int num_of_pkts;
	int i = 0;

        if (argc != 4) {
           printf("usage: %s <device> <# packets> <#labels>\ndevice = device to send on e.g. eth0\nnumber of arguments = %u\n", argv[0], argc);
           return -1;
        }

	num_of_pkts = atoi(argv[2]);
	
	/* Set the packet to all A's */
	
	memset(packet, 'A', PACKET_LENGTH);
	
	unsigned int num_labels = atoi(argv[argc-1]);



	if (!num_labels) {
	        write_ethernet_header(packet_pos, ETH_TYPE_IP);
	} else {
		write_ethernet_header(packet_pos, ETH_TYPE_MPLS_UNICAST);
	}
	packet_pos += MPLS_HDR_ADDR;
       

	printf("Enter labels starting from top of stack:\n"
	       "------------------------------------------\n");
	for (i = 0; i < num_labels; i++)
	{
		printf("Enter label value for label %u: ", i);
		scanf("%s",scanfstr);
		label = atoi(scanfstr);
		printf("Enter exp value for label %u: ", i);
		scanf("%s",scanfstr);
		exp = atoi(scanfstr);
		printf("Enter ttl value for label %u: ", i);
		scanf("%s",scanfstr);
		ttl = atoi(scanfstr);
		printf("i = %u num_labels = %u\n", i, num_labels);
		if (i == num_labels -1) {
		 	write_mpls_header(packet_pos, label, exp, 1, ttl);
		} else {
		 	write_mpls_header(packet_pos, label, exp, 0, ttl);
		}
		packet_pos += 4;
	}

	ip_pos = packet_pos;
        write_ip_header(packet_pos, PACKET_LENGTH - (ip_pos - packet));
	packet_pos += 20;

        write_udp_header(packet_pos, PACKET_LENGTH -(packet_pos - packet));
	packet_pos += 8;

 	write_ip_csum(ip_pos, 20);

	/* Create the raw socket */

	raw = CreateRawSocket(ETH_P_ALL);

	/* Bind raw socket to interface */

	BindRawSocketToInterface(argv[1], raw, ETH_P_ALL);


	while((num_of_pkts--)>0)
	{

		if(!SendRawPacket(raw, packet, PACKET_LENGTH))
		{
			perror("Error sending packet");
		}
		else
		{
			printf("Packet sent successfully\n");
		}
	}

	close(raw);

	return 0;
}

