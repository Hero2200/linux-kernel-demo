/*
 * =====================================================================================
 *       Filename:  chr_dev.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017年04月01日 14时55分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *   Organization:  
 * =====================================================================================
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/string.h>
#define printf printk

#define	DEVICE_NAME "demo_dev"

static char demo_buf[64];
static ssize_t demo_read(struct file *filp, char *buf, size_t count,
		loff_t *pos)
{
	ssize_t len;
	char string[]="abcde\n";
	printf ( "-- demo_read\n" );
	//copy_to_user(void __user *to, const void *from, unsigned long n)

	len = copy_to_user(buf, string, strlen(string));
	printf ( "len=%lu\n",len );

	return len;
}

static ssize_t demo_write(struct file *filp, const char *buf, size_t count,
		loff_t *pos)
{
	ssize_t len;
	int tmp;
	printf ( "-- demo_write\n" );
	//copy_from_user(void *to, const void __user *from, unsigned long n)
	len = copy_from_user(demo_buf, buf, strlen(buf));
	sscanf(buf,"%d\n",&tmp);

	printf ( "len=%lu tmp=%d",len,tmp );
	return len;
}

static dev_t devno;
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = demo_read,
	.write = demo_write,
};
static struct cdev demo_cdev;
static unsigned int demo_major;
static struct class *demo_cls;

static int __init demo_init(void)
{
	int ret;
	printf ( "--liuj demo_init\n" );
	cdev_init(&demo_cdev, &fops);
	demo_cdev.owner = THIS_MODULE;
	ret = alloc_chrdev_region(&devno, 0, 1, DEVICE_NAME);
	if(ret<0){

		printf ( "alloc chrdev number failed=%d\n",ret );
		return -1;
	}
	demo_major = MAJOR(devno);
	cdev_add(&demo_cdev,devno, 1);

	demo_cls = class_create(THIS_MODULE, DEVICE_NAME);
	//struct device *device_create(struct class *class, struct device *parent,
	//			     dev_t devt, void *drvdata, const char *fmt, ...)
	device_create(demo_cls, NULL, devno, NULL, DEVICE_NAME);

	snprintf(demo_buf, 64, "112233\n");
	return 0;
}

static void __exit demo_exit(void)
{
	printf ( "--liuj demo_exit\n" );
	device_destroy(demo_cls, devno);
	class_destroy(demo_cls);
	//unregister_chrdev_region
	unregister_chrdev_region(devno, 1);
	cdev_del(&demo_cdev);
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
