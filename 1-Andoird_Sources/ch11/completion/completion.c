#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
  
//  定义设备文件名
#define DEVICE_NAME "completion"

static struct completion my_completion;
static int completion_type = 0; // 0: complete    1: complete_all

static ssize_t demo_read(struct file *file, char __user *buf, size_t count,
        loff_t *ppos)
{
	printk("read start completion.done:%d\n", my_completion.done);
	wait_for_completion(&my_completion);
	printk("read end completion.done:%d\n", my_completion.done);
	return 0;
}

static ssize_t demo_write(struct file *file, const char __user *buf,
        size_t count, loff_t *ppos)
{
	printk("write start completion.done:%d\n", my_completion.done);
	if (completion_type == 0)
		complete(&my_completion);
	else if (completion_type == 1)
		complete_all(&my_completion);
	printk("write end completion.done:%d\n", my_completion.done);
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
	init_completion(&my_completion);

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
module_param(completion_type, int, S_IRUGO|S_IWUSR);
MODULE_LICENSE("GPL");
