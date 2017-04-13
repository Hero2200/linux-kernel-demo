#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>

#define	printf printk			/*  */
#define	DEVICE_NAME "demo_dev"			/*  */

static struct completion my_completion;
static int my_flag=0;

static ssize_t demo_read(struct file *filp, char *buf, size_t count,
        loff_t *pos)
{

    printf ( "demo_read\n" );
    printf ( "read start completion.done=%d\n",my_completion.done );
    wait_for_completion(&my_completion);
    printf ( "read end completion.done=%d\n",my_completion.done );
    return 0;
}

static ssize_t demo_write(struct file *filp, const char *buf, size_t count,
        loff_t *pos)
{

    printf ( "demo_write\n" );
    printf ( "read start completion.done=%d\n",my_completion.done );
    if(my_flag == 0)//only completion one task
        complete(&my_completion);
    else if(my_flag ==1 )
        complete_all(&my_completion);
    printf ( "read end completion.done=%d\n",my_completion.done );

    return count;
}

static struct file_operations dev_fops =
{
    .owner = THIS_MODULE,
    .read = demo_read,
    .write = demo_write,
};

static struct miscdevice misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &dev_fops,
};

static int __init demo_init(void)
{
    int ret;
    printf ( "demo_init register misc\n" );
    ret = misc_register(&misc);
	init_completion(&my_completion);

    return ret;
}

static void __exit demo_exit(void)
{

    printf ( "demo_exit deregister misc\n" );
    misc_deregister(&misc);

}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
