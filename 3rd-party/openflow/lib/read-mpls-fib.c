// MAH: start
// Parse an XML file specifying a FIB for an MPLS switch
// This code uses the libxml2 library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include <libxml/xmlmemory.h>
#include <libxml/parser.h>


#include <arpa/inet.h>
#include "openflow/openflow.h"
#include "packets.h"
#include "rconn.h"
#include "mpls-fib.h"
#include "mpls-switch.h"
#include "read-mpls-fib.h"

// Convert a colon delimited Ethernet address string
// into a 6 byte Ethernet address in network byte order
void eth_atoi(char *eth_str, uint8_t eth_addr[]) {
	// Note: no error checking. It's up to the caller to make
	// sure eth_str and eth_addr are properly allocated
	int i = 0;
	char *p = eth_str;
	// split colon delimited Ethernet string into 6
	// separate null terminated strings
	while (*p != 0) {
		if (*p == ':') *p = 0;
		p++;
	}

	// convert ASCII values into numeric values
	for (i = 0; i < ETH_ADDR_LEN; i++) {
		eth_addr[i] = strtol(&eth_str[3*i], NULL, 16);
	}
}

// Parse the dotted decimal notation (i.e. 192.168.1.1/24)
// Return the numeric representation and convert the bitmask to
// the OpenFlow wildcard for network addresses
uint32_t parse_ip_addr(char *ip_addr_str, uint32_t *wildcards) {
	char *p = ip_addr_str;
	*wildcards = 0;
	while (*p != 0) {
		if (*p == '/') {
			// terminate ip string before /
			*p = 0;
			p++;
			 // convert value after slash to integer in network byte order
			*wildcards = htonl((32 - atoi(p)) << OFPFW_NW_SRC_SHIFT);
			break;
		}
		p++;
	}
	// convert value before slash to integer in network byte order
	return inet_addr(ip_addr_str);
}


static struct pop_params*
parse_pop_option(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
	xmlChar *str;

	struct pop_params *ret = (struct pop_params *)malloc(sizeof(struct pop_params));
	if (ret == NULL) {
		fprintf(stderr,"out of memory\n");
		return(NULL);
	}
	memset(ret, 0, sizeof(nhlfe));
	printf("		pop action\n");
	/* We don't care what the top level element name is */
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		str = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "out_port"))) {
			ret->out_port = (uint32_t)atol((char *)str);
			printf("		out_port = %u\n", ret->out_port);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "src_mac"))) {
			eth_atoi((char *)str, ret->src_mac);
			printf("		src_mac = %x:%x:%x:%x:%x:%x\n",
					ret->src_mac[0], ret->src_mac[1], ret->src_mac[2], ret->src_mac[3],
					ret->src_mac[4], ret->src_mac[5]);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "dst_mac"))) {
			eth_atoi((char *)str, ret->dst_mac);
			printf("		dst_mac = %x:%x:%x:%x:%x:%x\n",
					ret->dst_mac[0], ret->dst_mac[1], ret->dst_mac[2], ret->dst_mac[3],
					ret->dst_mac[4], ret->dst_mac[5]);
		}

		free(str);
		cur = cur->next;
	}

	return ret;
}

static struct push_params*
parse_push_option(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
	xmlChar *str;

	struct push_params *ret = (struct push_params *)malloc(sizeof(struct push_params));
	if (ret == NULL) {
		fprintf(stderr,"out of memory\n");
		return(NULL);
	}
	memset(ret, 0, sizeof(nhlfe));
	//printf("		push action\n");

	/* We don't care what the top level element name is */
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		str = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "out_port"))) {
			ret->out_port = (uint32_t)atol((char *)str);
			//printf("		out_port = %u\n", ret->out_port);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "src_mac"))) {
			eth_atoi((char *)str, ret->src_mac);
			//printf("		src_mac = %x:%x:%x:%x:%x:%x\n",
			//					ret->src_mac[0], ret->src_mac[1], ret->src_mac[2], ret->src_mac[3],
			//					ret->src_mac[4], ret->src_mac[5]);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "dst_mac"))) {
			eth_atoi((char *)str, ret->dst_mac);
			//printf("		dst_mac = %x:%x:%x:%x:%x:%x\n",
			//					ret->dst_mac[0], ret->dst_mac[1], ret->dst_mac[2], ret->dst_mac[3],
			//					ret->dst_mac[4], ret->dst_mac[5]);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "mpls_label"))) {
			ret->mpls_label = (uint32_t)atol((char*)str);
			//printf("		mpls_label = %u\n", ret->mpls_label);
		}

		free(str);
		cur = cur->next;
	}

	return ret;
}

static struct swap_params*
parse_swap_option(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
	xmlChar *str;

	struct swap_params *ret = (struct swap_params *)malloc(sizeof(struct swap_params));
	if (ret == NULL) {
		fprintf(stderr,"out of memory\n");
		return(NULL);
	}
	memset(ret, 0, sizeof(nhlfe));
	//printf("		swap action\n");
	/* We don't care what the top level element name is */
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		str = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "out_port"))) {
			ret->out_port = (uint32_t)atol((char *)str);
	//		printf("						  		out_port = %u\n", ret->out_port);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "src_mac"))) {
			eth_atoi((char *)str, ret->src_mac);
	//		printf("		src_mac = %x:%x:%x:%x:%x:%x\n",
	//							ret->src_mac[0], ret->src_mac[1], ret->src_mac[2], ret->src_mac[3],
	//							ret->src_mac[4], ret->src_mac[5]);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "dst_mac"))) {
			eth_atoi((char *)str, ret->dst_mac);
	//		printf("		dst_mac = %x:%x:%x:%x:%x:%x\n",
	//							ret->dst_mac[0], ret->dst_mac[1], ret->dst_mac[2], ret->dst_mac[3],
	//							ret->dst_mac[4], ret->dst_mac[5]);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "mpls_label"))) {
			ret->mpls_label = (uint32_t)atol((char*)str);
	//		printf("		mpls_label = %u\n", ret->mpls_label);
		}

		free(str);
		cur = cur->next;
	}

	return ret;
}



// Parse an NHLFE action
// XXX Note: this currently assumes there is only one action per NHFLE entry
static nhlfePtr
parse_nhlfe(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur, struct mpls_switch *sw, struct ofp_match *match) {
	nhlfePtr ret = NULL;
	struct ofp_mpls_op_header *action;
	struct pop_params *pop;
	struct push_params *push;
	struct swap_params *swap;

    // allocate the struct
    ret = (nhlfePtr) malloc(sizeof(nhlfe));
    if (ret == NULL) {
        fprintf(stderr,"out of memory\n");
		return(NULL);
    }
    memset(ret, 0, sizeof(nhlfe));

//    printf("========================= NHLFE ===== \n");


    // We don't care what the top level element name is
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "pop"))) {
			pop = parse_pop_option(doc, ns, cur);
			if (pop) {
				action = make_pop_action(sw, pop, match);
				if (action) {
					ret->actions = action;
					ret->actions_len = action->len;
			//		printf("parse_nhlfe: got a valid pop action!\n");
				}
			}
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "push"))) {
			push = parse_push_option(doc, ns, cur);
			if (push) {
				action = make_push_action(sw, push, match);
				if (action) {
					ret->actions = action;
					ret->actions_len = action->len;
				//	printf("parse_nhlfe: got a valid push action!\n");
				}
			}
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "swap"))) {
			swap = parse_swap_option(doc, ns, cur);
			if (swap) {
				action = make_swap_action(sw, swap, match);
				if (action) {
					ret->actions = action;
					ret->actions_len = action->len;
//					printf("parse_nhlfe: got a valid swap action!\n");
				}
			}
		}

		cur = cur->next;
    }
  //  printf("===================================== \n");
    return(ret);
}



/*static void
printIlmEntry(ilmPtr cur) {

    if (cur == NULL) return;
    printf("=======  ILM\n");
	printf("	in_port: %u\n", cur->in_port);
	printf("	mpls_label: %u\n", cur->mpls_label);
    printf("======= \n");
}*/

static ilmPtr
parse_ilm(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur, struct mpls_switch *sw) {
	ilmPtr ret = NULL;
	xmlChar *str;
	nhlfePtr nhlfe_entry;
	struct ofp_match match;


	// initialize match
	memset(&match, 0, sizeof(struct ofp_match));
	match.dl_type = htons(ETH_TYPE_MPLS_UNICAST);
	match.wildcards = htonl((OFPFW_ALL) ^ ((OFPFW_IN_PORT) | (OFPFW_DL_TYPE) |
							(OFPFW_MPLS_L1) | (OFPFW_MPLS_L2)));

	// allocate the struct
    ret = (ilmPtr) malloc(sizeof(ilm));
    if (ret == NULL) {
        fprintf(stderr,"out of memory\n");
		return(NULL);
    }
    memset(ret, 0, sizeof(ilm));

    // We don't care what the top level element name is
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
    	str = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "in_port"))) {
			ret->in_port = (uint32_t)atol((char *)str);
			match.in_port = htons(ret->in_port);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "mpls_label"))) {
			ret->mpls_label = (uint32_t)atol((char *)str);
			match.mpls_label1 = htonl(ret->mpls_label);
			match.mpls_label2 = htonl(MPLS_INVALID_LABEL);
		}

		// XXX parse_nhlfe must be called last otherwise the ofp_match struct
		// will be incomplete
		// Note: assumes only one NHFLE per entry
		else if ((!xmlStrcmp(cur->name, (const xmlChar *) "NHLFE"))) {
			nhlfe_entry = parse_nhlfe(doc, ns, cur, sw, &match);
			if (nhlfe_entry) {
//				printf("parse_ilm: got an nhlfe_entry! actions_len = %u\n", nhlfe_entry->actions_len);
				nhlfe_entry->next_entry = NULL;
				ret->nhlfe = nhlfe_entry;
			}
		}

		free(str);
		cur = cur->next;
    }

    return(ret);

}

/*static void
printFtnEntry(ftnPtr cur) {
	struct in_addr addr;

    if (cur == NULL) return;
    printf("============ FTN ============= \n");
    printf("	FEC:\n");
    printf("	-------------------------:\n");
	printf("	in_port = %u\n", cur->FEC.in_port);
    printf("	dl_src: %x:%x:%x:%x:%x:%x\n", cur->FEC.dl_src[0],
    		cur->FEC.dl_src[1],	cur->FEC.dl_src[2], cur->FEC.dl_src[3],
    		cur->FEC.dl_src[4], cur->FEC.dl_src[5]);
    printf("	dl_src: %x:%x:%x:%x:%x:%x\n", cur->FEC.dl_dst[0],
        		cur->FEC.dl_dst[1],	cur->FEC.dl_dst[2], cur->FEC.dl_dst[3],
        		cur->FEC.dl_dst[4], cur->FEC.dl_dst[5]);
    printf("	dl_vlan = %u\n", cur->FEC.dl_vlan);
    printf("	dl_type = %u\n", cur->FEC.dl_type);
    addr.s_addr = htonl(cur->FEC.nw_src);
    printf("	nw_src: %s\n", inet_ntoa(addr));
    addr.s_addr = htonl(cur->FEC.nw_dst);
    printf("	nw_dst: %s\n", inet_ntoa(addr));
    printf("	nw_proto: %u\n", cur->FEC.nw_proto);
    printf("	tp_src: %u\n", cur->FEC.tp_src);
    printf("	tp_dst: %u\n", cur->FEC.tp_dst);
    printf("	-------------------------:\n");
    printf("============================== \n");
}*/

static ftnPtr
parse_ftn(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur, struct mpls_switch *sw) {
    ftnPtr ret = NULL;
	nhlfePtr nhlfe_entry;
    xmlChar *str;
    uint32_t ip_wildcards;

    struct ofp_match match; // in network byte order

	// initialize match
	memset(&match, 0, sizeof(struct ofp_match));
	match.mpls_label1 = htonl(MPLS_INVALID_LABEL);
	match.mpls_label2 = htonl(MPLS_INVALID_LABEL);
	// wildcard everything by default
	match.wildcards = htonl((OFPFW_ALL) ^ ((OFPFW_MPLS_L1) | (OFPFW_MPLS_L2)));

    // allocate the struct
    ret = (ftnPtr) malloc(sizeof(ftn));
    if (ret == NULL) {
        fprintf(stderr,"out of memory\n");
		return(NULL);
    }
    memset(ret, 0, sizeof(ftn));

    /* We don't care what the top level element name is */
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
    	str = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        if (!xmlStrcmp(cur->name, (const xmlChar *) "dl_type")) {
			ret->FEC.dl_type = (uint16_t)atoi((char *)str);
			match.dl_type = htons(ret->FEC.dl_type);
			match.wildcards = match.wildcards ^ htonl(OFPFW_DL_TYPE);
		}
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "dl_vlan")) {
        	ret->FEC.dl_vlan = (uint16_t)atoi((char *)str);
        	match.dl_vlan = htons(ret->FEC.dl_vlan);
        	match.wildcards = match.wildcards ^ htonl(OFPFW_DL_VLAN);
        }
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "in_port")) {
			ret->FEC.in_port = (uint16_t)atoi((char *)str);
			match.in_port = htons(ret->FEC.in_port);
			match.wildcards = match.wildcards ^ htonl(OFPFW_IN_PORT);
		}
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "dl_src")) {
			eth_atoi((char *)str, ret->FEC.dl_src);
			// already in network byte order
			memcpy(&match.dl_src,  &ret->FEC.dl_src, ETH_ADDR_LEN);
			match.wildcards = match.wildcards ^ htonl(OFPFW_DL_SRC);
		}
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "dl_dst")) {
			eth_atoi((char *)str, ret->FEC.dl_dst);
			// already in network byte order
			memcpy(&match.dl_dst,  &ret->FEC.dl_dst, ETH_ADDR_LEN);
			match.wildcards = match.wildcards ^ htonl(OFPFW_DL_DST);
		}
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "nw_src")) {
			ret->FEC.nw_src = ntohl(parse_ip_addr((char *)str, &ip_wildcards));
			match.nw_src = htonl(ret->FEC.nw_src);
			match.wildcards = (match.wildcards ^ ntohl(OFPFW_NW_SRC_MASK)) | ip_wildcards;
		}
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "nw_dst")) {
			ret->FEC.nw_dst = ntohl(parse_ip_addr((char *)str, &ip_wildcards));
			match.nw_dst = htonl(ret->FEC.nw_dst);
			match.wildcards = (match.wildcards ^ ntohl(OFPFW_NW_DST_MASK)) | ip_wildcards;
		}
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "nw_proto")) {
			ret->FEC.nw_proto = (uint16_t)atoi((char *)str);
			match.nw_proto = ret->FEC.nw_proto;
			match.wildcards = match.wildcards ^ htonl(OFPFW_NW_PROTO);
		}
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "tp_src")) {
			ret->FEC.tp_src = (uint16_t)atoi((char *)str);
			match.tp_src = htons(ret->FEC.tp_src);
			match.wildcards = match.wildcards ^ htonl(OFPFW_TP_SRC);
		}
        else if (!xmlStrcmp(cur->name, (const xmlChar *) "tp_dst")) {
       		ret->FEC.tp_dst = (uint16_t)atoi((char *)str);
       		match.tp_dst = htons(ret->FEC.tp_dst);
       		match.wildcards = match.wildcards ^ htonl(OFPFW_TP_DST);
      	}

		// XXX parse_nhlfe must be called last otherwise the match struct
		// will be incomplete
        // Note: assumes only one NHFLE per entry
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "NHLFE"))) {
        	nhlfe_entry = parse_nhlfe(doc, ns, cur, sw, &match);
			if (nhlfe_entry) {
	//			printf("parse_ftn: got an nhlfe_entry! actions_len = %u\n", nhlfe_entry->actions_len);
				nhlfe_entry->next_entry = NULL;
				ret->nhlfe = nhlfe_entry;
			}
		}
        // XXX FEC stores all but the wildcards in host byte order
        // wildcards bitmap is in network byte order
        ret->FEC.wildcards = match.wildcards;

        free(str);
		cur = cur->next;
    }

    return(ret);
}

static ilmPtr
parse_ilm_table(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur, struct mpls_switch *sw) {
	ilmPtr ilmEntry = NULL;
	ilmPtr ilmTable = NULL;

	//printf("parse_ilm_table\n");
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
    	if (!ilmTable) {
    		ilmEntry = parse_ilm(doc, ns, cur, sw);
    		ilmTable = ilmEntry;
    	} else {
    		ilmEntry->next_entry = parse_ilm(doc, ns, cur, sw);
    		ilmEntry = ilmEntry->next_entry;
    	}
    	cur = cur->next;
    }

    ilmEntry = ilmTable;
    while (ilmEntry != NULL) {
    	//printIlmEntry(ilmEntry);
    	ilmEntry = ilmEntry->next_entry;
    }
    return ilmTable;
}

static ftnPtr
parse_ftn_table(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur, struct mpls_switch *sw) {
	ftnPtr ftnEntry = NULL;
	ftnPtr ftnTable = NULL;

	//printf("parse_ftn_table\n");
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
    	if (!ftnTable) {
    		ftnEntry = parse_ftn(doc, ns, cur, sw);
    		ftnTable = ftnEntry;
    	} else {
    		ftnEntry->next_entry = parse_ftn(doc, ns, cur, sw);
    		ftnEntry = ftnEntry->next_entry;
    	}
    	cur = cur->next;
    }

    ftnEntry = ftnTable;
    while (ftnEntry != NULL) {
    	//printFtnEntry(ftnEntry);
    	ftnEntry = ftnEntry->next_entry;
    }
    return ftnTable;
}

static mplsFibPtr
parse_mpls_fib_file(char *filename, struct mpls_switch *sw) {
    xmlDocPtr doc;
    mplsFibPtr ret;
    xmlNodePtr cur;

	doc = xmlParseFile(filename);
    if (doc == NULL) return(NULL);

	cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return(NULL);
    }



	if (xmlStrcmp(cur->name, (const xmlChar *) "MPLS_FIB")) {
        fprintf(stderr,"document of the wrong type, root node != MPLS_FIB");
		xmlFreeDoc(doc);
		return(NULL);
    }

	/*
     * Allocate the structure to be returned.
     */

    ret = (mplsFibPtr) malloc(sizeof(mplsFib));
    if (ret == NULL) {
        fprintf(stderr,"out of memory\n");
		xmlFreeDoc(doc);
		return(NULL);
    }
    memset(ret, 0, sizeof(mplsFib));

	/*
     * Now, walk the tree.
     */
    cur = cur->xmlChildrenNode;
    while (cur) {
    	if (!(xmlStrcmp(cur->name, (const xmlChar *) "FTN_Table"))) {
    		ret->ftnTable = parse_ftn_table(doc, NULL, cur, sw);
    	}
    	if (!(xmlStrcmp(cur->name, (const xmlChar *) "ILM_Table"))) {
    		ret->ilmTable = parse_ilm_table(doc, NULL, cur, sw);
    	}
    	cur = cur->next;
    }

    return(ret);
}


mplsFibPtr read_mpls_fib(char *mpls_fib_file, struct mpls_switch *sw)
{
	mplsFibPtr cur;

    // COMPAT: Do not generate nodes for formatting spaces
    LIBXML_TEST_VERSION
    xmlKeepBlanksDefault(0);


	cur = parse_mpls_fib_file(mpls_fib_file, sw);
    if (! cur ) {
      fprintf( stderr, "Error parsing file '%s'\n", mpls_fib_file);
    }
    // Clean up everything else before quitting.
    xmlCleanupParser();

    return(cur);
}

// MAH: end
