/*
 * trh.h
 *
 *  Created on: Feb 19, 2018
 *      Author: root
 */

#ifndef INCLUDE_OPENVSWITCH_TRH_H_
#define INCLUDE_OPENVSWITCH_TRH_H_

#ifdef  __cplusplus
extern "C" {
#endif

struct hvnf_tlv {
	ovs_be32 hvnfUID_length; //Twenty-four bits h-VNF UID, Eight bits length.
	uint8_t vltp[]; //Variable Length Treatment Payload
};

struct trh_hdr {
	uint8_t  ip6t_nxt;		/* next header.  */
	uint8_t  ip6t_len;		/* length in units of 8 octets.  */

	uint16_t ip6t_ver__opt; // Four bits ipt6t_ver, Twelve bits ip6t_opt
	uint32_t ip6t_nxt_hvnf_uid__flags; //Twenty-four bits ip6t_nxt_hvnf_uid, Eight bits ip6t_flags

	//---------TR ID---------
	struct in6_addr ip6t_trid_src;      /* source address */
	struct in6_addr ip6t_trid_dst;      /* destination address */
	u_int16_t ip6t_trid_sport;		    /* source port */
	u_int16_t ip6t_trid_dport;		    /* destination port */

	//---------NF TLVs start here at octet 44-------
	//struct hvnf_tlv[] tlvs;
	ovs_be64 pad[1];
};


#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_OPENVSWITCH_TRH_H_ */
