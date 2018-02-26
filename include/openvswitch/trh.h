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
#define TRH_STATIC_LEN 8 //Length of the part of the header that is non-variable-length (no TLVs)
struct trh_hdr {
	uint8_t  ip6trh_nxt;		/* next header.  */
	uint8_t  ip6trh_len;		/* length in units of 8 octets.  */

	uint16_t ip6trh_ver__opt; // Four bits ipt6t_ver, Twelve bits ip6t_opt
	uint32_t ip6trh_nxt_hvnf_uid__flags; //Twenty-four bits ip6t_nxt_hvnf_uid, Eight bits ip6t_flags

	/* Rest of the header should be irrelevant for OVS at this moment.
	//---------TR ID---------
	struct in6_addr ip6t_trid_src;
	struct in6_addr ip6t_trid_dst;
	uint16_t ip6t_trid_sport;
	uint16_t ip6t_trid_dport;
	//---------NF TLVs start here at octet 44-------
	//struct hvnf_tlv[] tlvs;
	//ovs_be64 pad;
	*/
};


#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_OPENVSWITCH_TRH_H_ */
