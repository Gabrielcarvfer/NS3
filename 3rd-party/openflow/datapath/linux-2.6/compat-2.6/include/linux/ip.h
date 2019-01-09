#ifndef __LINUX_IP_WRAPPER_H
#define __LINUX_IP_WRAPPER_H 1

#include_next <linux/ip.h>

#include <linux/version.h>
#if ((LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)) && \
	(RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION(5,2)))

#ifdef __KERNEL__
#include <linux/skbuff.h>

static inline struct iphdr *ip_hdr(const struct sk_buff *skb)
{
	return (struct iphdr *)skb_network_header(skb);
}

static inline unsigned int ip_hdrlen(const struct sk_buff *skb)
{
	return ip_hdr(skb)->ihl * 4;
}
#endif /* __KERNEL__ */

#endif /* linux kernel < 2.6.22 */

#endif
