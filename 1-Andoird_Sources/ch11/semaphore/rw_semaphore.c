#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <linux/delay.h>
//  定义设备文件名
#define DEVICE_NAME "rw_semaphore"
struct rw_semaphore rw_sem;

static ssize_t demo_read(struct file *file, char __user *buf, size_t count,
        loff_t *ppos)
{

	struct timeval tv;
	do_gettimeofday(&tv);
	printk("read:start sec:%ld\n", tv.tv_sec);
	down_read(&rw_sem);
	do_gettimeofday(&tv);
	printk("read:end sec:%ld\n", tv.tv_sec);
	mdelay(5000);
	up_read(&rw_sem);
	return 0;

}

static ssize_t demo_write(struct file *file, const char __user *buf,
        size_t count, loff_t *ppos)
{
	struct timeval tv;
	do_gettimeofday(&tv);
	printk("write:start sec:%ld\n", tv.tv_sec);
	down_write(&rw_sem);
	do_gettimeofday(&tv);
	printk("write:end sec:%ld\n", tv.tv_sec);
	up_write(&rw_sem);
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
    init_rwsem(&rw_sem);
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
