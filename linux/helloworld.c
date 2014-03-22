#include "helloworld.h"

#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <nv-p2p.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello kernel world!");
MODULE_AUTHOR("Rick Veens");


/* File operations prototypes and struct */
static int helloworld_open(struct inode *inode, struct file *filp);
static int helloword_release(struct inode *inode, struct file *filp);
static ssize_t helloworld_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t helloworld_write(struct file *, const char __user *, size_t, loff_t *);

struct file_operations hello_fops = {
	.owner = 	THIS_MODULE,
	.open = 	helloworld_open,
	.read = 	helloworld_read,
	.write = 	helloworld_write,
	.release =	helloword_release,
};

/* Proc filesystem function prototypes and struct */
ssize_t helloworld_proc_read(struct file *filp, char *buffer, size_t length, loff_t *offset);

struct file_operations hello_proc_fops = {
	.read = helloworld_proc_read,
};

/* Init and release functions */
static int __init helloworld_init(void);
static void __exit helloworld_exit(void);

/* Module global variables */
static dev_t hello_devt;			// Device number registration
static struct cdev *hello_cdev;			// Character device
static struct proc_dir_entry *hello_proc; 	// Proc directory entry
/* Module variables for operation */ 
static char *memory;				// Pointer to memory
static int memory_size = 1000;			// Memory to allocate
static char *initial_data = "test";		// Initial memory data

module_param(memory_size, int, 0);
module_param(initial_data, charp, 0);

static int __init helloworld_init(void)
{
	int result;

	PDEBUG("init\n");
	PDEBUG("memory= '%s'\n", memory);

	// TODO check voor errors, concurrency

	/* allocate a memory area */
	memory = kcalloc(memory_size, 1, GFP_KERNEL);
	if (!memory) {
		PDEBUG("error allocating memory\n");
		return -1;
	}
	/* insert initial data into memory */
	memcpy(memory, initial_data, sizeof(char) * strlen(initial_data));

	/* Get a range of major, minor numbers. */
	result = alloc_chrdev_region(&hello_devt, 0, 1, "helloworld");
	if (result < 0) {
		PDEBUG("allocate device\n");
		return result;
	}
	char *test = kmalloc(sizeof(char)*1000, GFP_KERNEL);
	PDEBUG("registered device %s\n", format_dev_t(test, hello_devt));
	kfree(test);

	/* Register character device, set file operations */
 	hello_cdev = cdev_alloc();
	if (!hello_cdev) {
		PDEBUG("can't alloc cdev.\n");
		goto fail;
	}
	hello_cdev->ops = &hello_fops;
	hello_cdev->owner = THIS_MODULE;
	result = cdev_add(hello_cdev, hello_devt, 1);
	if (result < 0) {
		PDEBUG("adding device to kernel failed.\n");
		goto fail;
	}

	/* Create proc file */
	hello_proc = proc_create("driver/helloworldmem", 0, NULL, &hello_proc_fops);
	if (!hello_proc) {
		PDEBUG("adding proc dirent failed");
		goto fail;
	}

	return 0;

	fail:
		PDEBUG("fail during initialization!\n");
		/* helloworld_exit(); */
		return result;
}

static int helloworld_open(struct inode *inode, struct file *filp)
{
	PDEBUG("open\n");
	return 0;
}

static void __exit helloworld_exit(void)
{
	PDEBUG("exit\n");
	kfree(memory);
	cdev_del(hello_cdev);
	unregister_chrdev_region(hello_devt, 1);
	proc_remove(hello_proc);
}

static int helloword_release(struct inode *inode, struct file *filp)
{
	PDEBUG("release\n");
	return 0;
}

static ssize_t helloworld_read(struct file *filp, char __user *buff, size_t len, loff_t *off)
{
	static int finished = 0;

	if (finished) {
		finished = 0;
		return 0;
	}

	finished = 1;

	/* determine length to write */
	if (len > memory_size)
		len = memory_size;

	if (copy_to_user(buff, memory, len))
		return -EFAULT;

	return len;
}

static ssize_t helloworld_write(struct file *filp, const char __user *buff, size_t len, loff_t *off)
{
	static int finished = 0;

	if (finished) {
		finished = 0;
		return 0;
	}

	finished = 1;

	if (len > memory_size)
		len = memory_size;

	if (copy_from_user(memory, buff, len))
		return -EFAULT;

	return len;
}

ssize_t helloworld_proc_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
	static int finished = 0;

	if (finished) {
		finished = 0;
		return 0;
	}

	finished = 1;

	if (length > memory_size)
		length = memory_size;

	if (copy_to_user(buffer, memory, memory_size))
		return -EFAULT;

	return length;
}

module_init(helloworld_init);
module_exit(helloworld_exit);
