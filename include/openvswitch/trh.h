#ifndef __OPENVSWITCH_TRH_H
#define __OPENVSWITCH_TRH_H 1

#include "openvswitch/types.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define IPPROTO_TRH		144	  // IPv6 Treatment header

struct treatment_id
{
	struct in6_addr src;
	struct in6_addr dst;
	uint16_t sport;
	uint16_t dport;
};

struct hvnf_tlv {
	uint32_t uid_len; 		 //Twenty-four bits h-VNF UID, Eight bits length.
	uint8_t *vltp; 			 //Variable Length Treatment Payload
};

#define TRH_TLV_UID_MASK 0xffffff00
#define TRH_TLV_UID_SHIFT 8
#define TRH_TLV_LEN_MASK 0x000000ff

static inline uint32_t
trh_tlv_get_uid(const struct hvnf_tlv *tlv)
{
	return (ntohl(tlv->uid_len) & TRH_TLV_UID_MASK) >> TRH_TLV_UID_SHIFT;
}

static inline void
trh_tlv_set_uid(struct hvnf_tlv *tlv, ovs_be32 uid)
{
	tlv->uid_len = htonl((ntohl(tlv->uid_len) & TRH_TLV_LEN_MASK) |
						 ((ntohl(uid) << TRH_TLV_UID_SHIFT) & TRH_TLV_UID_MASK));
}

static inline uint8_t
trh_tlv_get_len(const struct hvnf_tlv *tlv)
{
	return ntohs(tlv->uid_len) & TRH_TLV_LEN_MASK;
}

static inline void
trh_tlv_set_len(struct hvnf_tlv *tlv, uint8_t len)
{
	tlv->uid_len = htonl((ntohl(tlv->uid_len) & TRH_TLV_UID_MASK) |
				         (len & TRH_TLV_LEN_MASK));
}

#define TRH_STATIC_LEN 44 //Length of the part of the header that is non-variable-length (no TLVs)

/* Treatment header */
struct ip6_trhdr
{
	uint8_t  ip6trh_nxt;		   // Next header
	uint8_t  ip6trh_len;		   // Length in units of 8 octets, excluding the first 8 octets (rfc6564 sec 4)
	uint16_t ip6trh_ver_opt;       // Four bits Version, Twelve bits Options
	uint32_t ip6trh_nextuid_flags; //Twenty-four bits Next h-VNF UID, Eight bitsFlags

	// Treatment ID
	struct treatment_id trid;

	// Followed by h-VNF specific TLVs starting at octet 44. Always has minimum one TLV
	struct hvnf_tlv tlvs[];
};

#define TRH_VER_MASK 0xf000
#define TRH_VER_SHIFT 12
#define TRH_OPT_MASK 0x0fff
#define TRH_NEXTUID_MASK 0xffffff00
#define TRH_NEXTUID_SHIFT 8
#define TRH_FLAGS_MASK 0x000000ff

static inline uint8_t
trh_get_ver(const struct ip6_trhdr *trh)
{
	return (ntohs(trh->ip6trh_ver_opt) & TRH_VER_MASK) >> TRH_VER_SHIFT;
}

static inline void
trh_set_ver(struct ip6_trhdr *trh, uint8_t ver)
{
	trh->ip6trh_ver_opt = htons((ntohs(trh->ip6trh_ver_opt) & TRH_OPT_MASK) |
						        ((ver << TRH_VER_SHIFT) & TRH_VER_MASK));
}

static inline uint16_t
trh_get_opt(const struct ip6_trhdr *trh)
{
	return ntohs(trh->ip6trh_ver_opt) & TRH_OPT_MASK;
}

static inline void
trh_set_opt(struct ip6_trhdr *trh, ovs_be16 opt)
{
	trh->ip6trh_ver_opt = htons((ntohs(trh->ip6trh_ver_opt) & TRH_VER_MASK) |
						   	    (ntohs(opt) & TRH_OPT_MASK));
}

static inline uint32_t
trh_get_nextuid(const struct ip6_trhdr *trh)
{
	return ntohl(trh->ip6trh_nextuid_flags) & TRH_NEXTUID_MASK;
}

static inline void
trh_set_nextuid(struct ip6_trhdr *trh, ovs_be32 nextuid)
{
	trh->ip6trh_nextuid_flags = htonl((ntohl(trh->ip6trh_nextuid_flags) & TRH_FLAGS_MASK) |
								      (ntohl(nextuid << TRH_NEXTUID_SHIFT) & TRH_NEXTUID_MASK));
}

static inline uint8_t
trh_get_flags(const struct ip6_trhdr *trh)
{
	return ntohl(trh->ip6trh_nextuid_flags) & TRH_FLAGS_MASK;
}

static inline void
trh_set_flags(struct ip6_trhdr *trh, uint8_t flags)
{
	trh->ip6trh_nextuid_flags = htonl((ntohl(trh->ip6trh_nextuid_flags) & TRH_NEXTUID_MASK) |
								      (flags & TRH_FLAGS_MASK));
}


#ifdef __cplusplus
}
#endif

#endif /* __OPENVSWITCH_TRH_H_ */
