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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/slab.h>
#define printf printk

#define	DEVICE_NAME "demo_dev"

#define	GL_SIZE 0x1000 /*  */
#define	MEM_CLEAR 0x1			/*  */
#define	GL_MAJOR 230			/*  */
static int gl_major = GL_MAJOR;
module_param(gl_major,int,0644);
struct gl_dev{
	struct cdev cdev;
	unsigned char mem[GL_SIZE];
} *gl_devp;

static int gl_open(struct inode *inode,struct file *filp)
{
	filp->private_data = gl_devp;
	return 0;
}

static int gl_release(struct inode *indoe, struct file *filp)
{
	return 0;
}

static long gl_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
	struct gl_dev *dev = filp->private_data;
	switch(cmd){
		case MEM_CLEAR:
			memset(dev->mem, 0 , GL_SIZE);
			break;
		default:
			return -EINVAL;
	}

	return 0;
}

static ssize_t gl_read(struct file *filp, char *buf, size_t count,
		loff_t *pos)
{
	unsigned long p =*pos;
	int ret;
	struct gl_dev *dev = filp->private_data;
	if(p >= GL_SIZE)
		return 0;
	if(count > GL_SIZE - p)
		count = GL_SIZE - p;
	if(copy_to_user(buf,dev->mem+p,count)){
		printf ( "read failed\n" );
		ret = -EFAULT;
	}else{
		*pos += count;
		ret = count;
		printf ( "read %lu byte from %lu\n",count,p );
	}

	return ret;
}


static ssize_t gl_write(struct file *filp, const char *buf, size_t count,
		loff_t *pos)
{
	unsigned long p= *pos;
	int ret;
	struct gl_dev *dev = filp->private_data;
	if(p >= GL_SIZE)
		return 0;
	if(count > GL_SIZE -p)
		count = GL_SIZE -p;
	if(copy_from_user(dev->mem + p, buf, count)){
		ret = -EFAULT;
	}else{
		*pos += count;
		ret = count;
		printf ( "write %lu byte from %lu\n",count,p );
	}
	return ret;
}

static loff_t gl_llseek(struct file *filp, loff_t off, int where)
{
	loff_t ret =0;
	switch(where){
		case 0:
			if(off < 0){
				ret = -EINVAL;
				break;
			}
			if((unsigned int)off > GL_SIZE){
				ret = -EINVAL; break;
			}
			filp->f_pos = (unsigned int)off;
			ret = filp->f_pos;
			break;
		case 1:
			if((filp->f_pos + off) > GL_SIZE){
				ret = -EINVAL;
				break;
			}
			if((filp->f_pos + off) < 0){
				ret = -EINVAL;
				break;
			}
			filp->f_pos += off;
			ret = filp->f_pos;
			break;
		default:
			ret = -EINVAL;
			break;
	}

	return ret;
}
static dev_t devno;
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = gl_read,
	.write = gl_write,
	.llseek = gl_llseek,
	.unlocked_ioctl = gl_ioctl,
	.open = gl_open,
	.release = gl_release,
};

static void gl_setup_cdev(struct gl_dev *dev, int index)
{
	int ret;
	devno = MKDEV(gl_major, index);
	cdev_init(&dev->cdev, &fops);
	dev->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->cdev, devno ,1);
	if(ret){
		printf ( "failed cdev_add\n" );
	}
}

static struct class *demo_cls;

static int __init gl_init(void)
{
	int ret;
	printf ( "--liuj demo_init\n" );
	/*1 register devno
	 */
	if(gl_major){
		dev_t devno = MKDEV(gl_major, 0);
		ret = register_chrdev_region(devno, 1, DEVICE_NAME);
	}else{
		ret = alloc_chrdev_region(&devno, 0, 1, DEVICE_NAME);
		if(ret<0){
			printf ( "alloc chrdev number failed=%d\n",ret );
			return -1;
		}
	}
	/* cdev_init */
	gl_devp = kzalloc(sizeof(struct gl_dev),GFP_KERNEL);
	if(!gl_devp){
		ret = -ENOMEM;
		goto fail_malloc;
	}
	gl_setup_cdev(gl_devp,0);

	demo_cls = class_create(THIS_MODULE, DEVICE_NAME);
	device_create(demo_cls, NULL, devno, NULL, DEVICE_NAME);
	return ret;

fail_malloc:
	unregister_chrdev_region(devno,1);

	return 0;
}

static void __exit gl_exit(void)
{
	printf ( "--liuj demo_exit\n" );
	device_destroy(demo_cls, devno);
	class_destroy(demo_cls);
	cdev_del(&gl_devp->cdev);
	kfree(gl_devp);
	unregister_chrdev_region(devno, 1);
}

module_init(gl_init);
module_exit(gl_exit);
MODULE_LICENSE("GPL");
