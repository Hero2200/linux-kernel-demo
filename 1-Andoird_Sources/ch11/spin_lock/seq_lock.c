#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <linux/delay.h>
#include <linux/random.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/tty.h>
#include <linux/sched.h>
#include <linux/serial.h>
#include <linux/mm.h>
#include <linux/generic_serial.h>
#include <linux/interrupt.h>
#include <linux/tty_flip.h>
#include <linux/delay.h>
#include <linux/gfp.h>

//  定义设备文件名
#define DEVICE_NAME "seq_lock"
static DEFINE_SEQLOCK(seqlock);

static ssize_t demo_read(struct file *file, char __user *buf, size_t count,
        loff_t *ppos)
{

	unsigned seq;
	do
	{

		seq = read_seqbegin(&seqlock);
		mdelay(10000);

	}while(read_seqretry(&seqlock, seq));

	return 0;

}

static ssize_t demo_write(struct file *file, const char __user *buf,
        size_t count, loff_t *ppos)
{
	struct timeval tv;
	do_gettimeofday(&tv);

	printk("write:start sec:%ld\n", tv.tv_sec);
	write_seqlock(&seqlock);

	do_gettimeofday(&tv);
	printk("write:end sec:%ld\n", tv.tv_sec);
	write_sequnlock(&seqlock);


	return count;
}
static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .read = demo_read, .write = demo_write };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

//  初始化Linux驱动
static int __init demo_init(void)
{
	//  建立设备文件
	int ret = misc_register(&misc);
	printk("demo_init_success\n");

	return ret;
}

// 卸载Linux驱动
static void __exit demo_exit(void)
{
	printk("demo_exit_success\n");
	//  删除设备文件
	misc_deregister(&misc);
}
//  注册初始化Linux驱动的函数
module_init( demo_init);
//  注册卸载Linux驱动的函数
module_exit( demo_exit);
MODULE_LICENSE("GPL");
