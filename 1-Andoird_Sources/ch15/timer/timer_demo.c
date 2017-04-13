#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/timer.h>
#include <asm/atomic.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/delay.h>



#define DEVICE_NAME "timer_demo"

struct timer_dev
{
	atomic_t counter; //  一共经历了多少秒？
	struct timer_list s_timer; // 设备要使用的定时器
};

struct timer_dev *timer_devp; // 设备结构体指针

// 定时器处理函数
static void timer_demo_handle(unsigned long arg)
{
	//  使定时器处理函数可以在下一秒执行
	mod_timer(&timer_devp->s_timer, jiffies + HZ);
	atomic_inc(&timer_devp->counter);
	printk(KERN_NOTICE "current jiffies is %ld\n", jiffies);
}

//  设备文件打开函数
int timer_demo_open(struct inode *inode, struct file *filp)
{
	//  初始化定时器
	init_timer(&timer_devp->s_timer);
	timer_devp->s_timer.function = &timer_demo_handle;
	timer_devp->s_timer.expires = jiffies + HZ;

	add_timer(&timer_devp->s_timer); // 添加（注册）定时器

	atomic_set(&timer_devp->counter, 0);
	//计数清0

	return 0;
}
//  设备文件释放函数
int timer_demo_release(struct inode *inode, struct file *filp)
{
	del_timer_sync(&timer_devp->s_timer);

	return 0;
}

// 设备文件的读函数
static ssize_t timer_demo_read(struct file *filp, char __user *buf,
        size_t count, loff_t *ppos)
{

	int counter;
	counter = atomic_read(&timer_devp->counter);
	if (put_user(counter, (int*)buf))
		return -EFAULT;
	else
		return sizeof(unsigned int);
}

/*文件操作结构体*/
static const struct file_operations timer_fops =
{ .owner = THIS_MODULE, .open = timer_demo_open, .release = timer_demo_release,
        .read = timer_demo_read };
static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &timer_fops };

/*设备驱动模块加载函数*/
int __init timer_demo_init(void)
{
	int ret = misc_register(&misc);
	/* 动态申请设备结构体的内存*/
	timer_devp = kmalloc(sizeof(struct timer_dev), GFP_KERNEL);
	if (!timer_devp) /*申请失败*/
	{
		misc_deregister(&misc);
		ret -ENOMEM;

	}
	else
	{
		memset(timer_devp, 0, sizeof(struct timer_dev));
	}

	return ret;
}

/*模块卸载函数*/
void __exit timer_demo_exit(void)
{
	kfree(timer_devp); //释放设备结构体内存
	misc_deregister(&misc);
}

MODULE_AUTHOR("Lining");
MODULE_LICENSE("GPL");

module_init(timer_demo_init);
module_exit(timer_demo_exit);
