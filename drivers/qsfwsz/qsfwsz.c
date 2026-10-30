// SPDX-License-Identifier: GPL-2.0
/*
 * QSFWSZ: minimal, metadata-only kernel diagnostic interface.
 *
 * This first version deliberately exposes no process-memory read/write
 * operations. Its ioctl ABI is kept small so future diagnostic extensions
 * can be reviewed independently.
 */

#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/qsfwsz.h>

static long qsfwsz_ioctl(struct file *file, unsigned int cmd,
			 unsigned long arg)
{
	struct qsfwsz_info info = {
		.abi_version = QSFWSZ_ABI_VERSION,
		.struct_size = sizeof(struct qsfwsz_info),
		.features = QSFWSZ_FEATURE_INFO,
		.reserved = { 0, 0 },
	};

	if (_IOC_TYPE(cmd) != QSFWSZ_IOC_MAGIC)
		return -ENOTTY;

	switch (cmd) {
	case QSFWSZ_IOC_GET_INFO:
		if (copy_to_user((void __user *)arg, &info, sizeof(info)))
			return -EFAULT;
		return 0;
	default:
		return -ENOTTY;
	}
}

static const struct file_operations qsfwsz_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = qsfwsz_ioctl,
	.llseek = no_llseek,
};

static struct miscdevice qsfwsz_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "qsfwsz",
	.fops = &qsfwsz_fops,
	.mode = 0600,
};

static int __init qsfwsz_init(void)
{
	return misc_register(&qsfwsz_device);
}

static void __exit qsfwsz_exit(void)
{
	misc_deregister(&qsfwsz_device);
}

module_init(qsfwsz_init);
module_exit(qsfwsz_exit);

MODULE_DESCRIPTION("QSFWSZ metadata-only kernel diagnostic interface");
MODULE_AUTHOR("8-Cores");
MODULE_LICENSE("GPL");
