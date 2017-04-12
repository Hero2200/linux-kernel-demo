/*
 * =====================================================================================
 *
 *       Filename:  demo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年04月10日 23时10分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>

#define	printf printk			/*  */
#define	DEVICE_NAME "demo_dev"			/*  */

static ssize_t demo_read(struct file *filp, char *buf, size_t count,
        loff_t *pos)
{

    printf ( "demo_read\n" );

    return 0;
}

static ssize_t demo_write(struct file *filp, const char *buf, size_t count,
        loff_t *pos)
{

    printf ( "demo_write\n" );

    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = demo_read,
    .write = demo_write,
};

static struct miscdevice misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &fops,
};

static int __init demo_init(void)
{
    int ret;
    printf ( "demo_init register misc\n" );
    ret = misc_register(&misc);

    return ret;
}

static void __exit demo_exit(void)
{

    printf ( "demo_exit\n" );
    misc_deregister(&misc);

}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
