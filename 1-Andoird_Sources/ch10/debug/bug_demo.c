#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

//  定义设备文件名
#define DEVICE_NAME "bug"

static ssize_t bug_demo_read(struct file *file, char __user *buf,
        size_t count, loff_t *ppos)
{
	  int *p=0;
	  *p  = 1;  //create oops
	return 0;
}


//  描述与设备文件触发的事件对应的回调函数指针
static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .read = bug_demo_read};

//  描述设备文件的信息
static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

//  初始化Linux驱动
static int __init bug_demo_init(void)
{
	int ret;
	//  建立设备文件
	ret = misc_register(&misc);
	printk("bug_demo_init_success\n");
	return ret;
}

// 卸载Linux驱动
static void __exit bug_demo_exit(void)
{
	//  删除设备文件
	misc_deregister(&misc);

	//  输出日志信息
	printk("bug_demo_exit_success\n");
}

//  注册初始化Linux驱动的函数
module_init( bug_demo_init);
//  注册卸载Linux驱动的函数
module_exit( bug_demo_exit);
