#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>


//  定义设备文件名
#define DEVICE_NAME "atomic"

static int atom = 0; //  0: 多个进程可以同时打开atomic设备文件
//  非0：同时只能有一个进程打开atomic设备文件

static atomic_t int_atomic_available = ATOMIC_INIT(1);

static int atomic_open(struct inode *node, struct file *file)
{

	if (atom)
	{
		if (!atomic_dec_and_test(&int_atomic_available))
		{
			atomic_inc(&int_atomic_available);
			return -EBUSY;
		}
	}

	return 0;
}
static int atomic_release(struct inode *node, struct file *file)
{
	if (atom)
	{
		atomic_inc(&int_atomic_available);
	}
	return 0;
}
static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .open = atomic_open, .release = atomic_release };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

//  初始化Linux驱动
static int __init atomic_init(void)
{
	//  建立设备文件
	int ret = misc_register(&misc);
	printk("atomic_init_success\n");

	return ret;
}

// 卸载Linux驱动
static void __exit atomic_exit(void)
{

	printk("atomic_exit_success\n");
	//  删除设备文件
	misc_deregister(&misc);
}
//  注册初始化Linux驱动的函数
module_init( atomic_init);
//  注册卸载Linux驱动的函数
module_exit( atomic_exit);
module_param(atom, int, S_IRUGO|S_IWUSR);
MODULE_LICENSE("GPL");
