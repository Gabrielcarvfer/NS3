#ifndef __COMPAT26_H
#define __COMPAT26_H 1

#include <linux/version.h>

#if defined(CONFIG_PREEMPT) && LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,21)
#error "CONFIG_PREEMPT is broken with 2.6.x before 2.6.21--see commit 4498121ca3, \"[NET]: Handle disabled preemption in gfp_any()\""
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,23)
/*----------------------------------------------------------------------------
 * In 2.6.24, a namespace argument became required for dev_get_by_name. */
#define net_init NULL

#define dev_get_by_name(net, name) \
		dev_get_by_name((name))

#endif /* linux kernel <= 2.6.23 */


#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,22)
/*----------------------------------------------------------------------------
 * In 2.6.23, the last argument was dropped from kmem_cache_create. */
#define kmem_cache_create(n, s, a, f, c) \
		kmem_cache_create((n), (s), (a), (f), (c), NULL)

#endif /* linux kernel <= 2.6.22 */

/* For CentOS / RHEL kernel compatibility */
#ifndef RHEL_RELEASE_VERSION
#define RHEL_RELEASE_VERSION(X,Y) ( 0 )
#endif

#endif /* compat26.h */
