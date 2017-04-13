#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

//  定义设备文件名
#define DEVICE_NAME "wordcount"
static unsigned char mem[10000]; // 保存向设备文件写入的数据
static char read_flag = 'y';     // y：已从设备文件读取数据   n：未从设备文件读取数据
static int written_count = 0;    // 向设备文件写入数据的字节数

//  从设备文件读取数据时调用改方法
static ssize_t word_count_read(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{   
	//  如果还没有读取设备文件中的数据，可以进行读取
	if(read_flag == 'n')
	{   
		//  将内核空间的数据复制用户空间，buf中的数据就是从设备文件做读出的数据
		copy_to_user(buf, (void*) mem, written_count);
		
		
		printk("read count:%d", (int) written_count);
		read_flag = 'y';
		return written_count;
	}
        //  已经从设备文件读取数据，不能再次读取数据
	else
	{   
		return 0;
	}
}
static ssize_t word_count_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{   
	//  将用户空间的数据复制内核空间，mem中的数据就是向设备文件写入的数据
	copy_from_user(mem, buf, count);
	read_flag = 'n';
	written_count = count;
	printk("written count:%d", (int)count);

	return count;
}
//  描述与设备文件触发的事件对应的回调函数指针
static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .read = word_count_read, .write = word_count_write };

//  描述设备文件的信息
static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

//  初始化Linux驱动
static int word_count_init(void)
{
	int ret;
	//  建立设备文件
	ret = misc_register(&misc);
	//  输出日志信息
	printk("word_count_init_success\n");
	return ret;
}

// 卸载Linux驱动
static void word_count_exit(void)
{
	//  删除设备文件
	misc_deregister(&misc);
	//  输出日志信息
	printk("word_init_exit_success\n");
}

//  注册初始化Linux驱动的函数
module_init( word_count_init);
//  注册卸载Linux驱动的函数
module_exit( word_count_exit);

MODULE_AUTHOR("lining");
MODULE_DESCRIPTION("statistics of word count.");
MODULE_ALIAS("word count module.");
MODULE_LICENSE("GPL");
