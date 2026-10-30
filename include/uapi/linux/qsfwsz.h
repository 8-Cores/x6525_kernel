/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _UAPI_LINUX_QSFW SZ_H
#define _UAPI_LINUX_QSFW SZ_H

#include <linux/ioctl.h>
#include <linux/types.h>

#define QSFWSZ_IOC_MAGIC	0xF5
#define QSFWSZ_ABI_VERSION	1

#define QSFWSZ_FEATURE_INFO	(1ULL << 0)

struct qsfwsz_info {
	__u32 abi_version;
	__u32 struct_size;
	__u64 features;
	__u64 reserved[2];
};

#define QSFWSZ_IOC_GET_INFO \
	_IOR(QSFWSZ_IOC_MAGIC, 0x00, struct qsfwsz_info)

#endif /* _UAPI_LINUX_QSFW SZ_H */
