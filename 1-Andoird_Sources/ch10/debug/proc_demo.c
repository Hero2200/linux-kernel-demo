#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#define PROC_NAME_BASE "proc_demo"
#define PROC_NAME "bin2dec"
#define PROC_NAME_READONLY "readonly"

static long decimal;

static struct proc_dir_entry *proc_entry_base = NULL;
static struct proc_dir_entry *proc_entry = NULL;
static struct proc_dir_entry *proc_entry_readonly = NULL;

static int proc_demo_readonly(char *page, char **start, off_t off, int count,
        int *eof, void *data)
{

	int len;

	if (off > 0)
	{
		*eof = 1;
		return 0;
	}
	len = sprintf(page, "debug information\n");
	return len;
}

static int proc_demo_read(char *page, char **start, off_t off, int count,
        int *eof, void *data)
{
	int len;

	if (off > 0)
	{
		*eof = 1;
		return 0;
	}
	len = sprintf(page, "%ld\n", decimal);
	return len;
}

static int proc_demo_write(struct file *file, const char __user *buffer,
        unsigned long count, void *data)
{
	char buf[count];
	int ret;
	if (copy_from_user(buf, buffer, count))
	{
		ret = -EFAULT;
		goto err;
	}
	else
	{
		decimal = simple_strtoul(buf, NULL, 2);

		return count;
	}

	err: return ret;

}

//  初始化Linux驱动
static int __init proc_demo_init(void)
{
	proc_entry_base = proc_mkdir(PROC_NAME_BASE, NULL);
	if (proc_entry_base == NULL)
	{
		printk(KERN_INFO"Couldn't create proc entry dir\n");
		goto err;
	}
	proc_entry = create_proc_entry(PROC_NAME, 0666, proc_entry_base);
	proc_entry_readonly = create_proc_read_entry(PROC_NAME_READONLY, 0444,
	        proc_entry_base, proc_demo_readonly, NULL);

	if (proc_entry == NULL || proc_entry_readonly == NULL)
	{
		printk(KERN_INFO"Couldn't create proc entry\n");

		goto err;
	}
	else
	{
		proc_entry->read_proc = proc_demo_read;
		proc_entry->write_proc = proc_demo_write;

	}
	return 0;
	err: return -ENOMEM;

}

// 卸载Linux驱动
static void __exit proc_demo_exit(void)
{
	if (proc_entry != NULL)
		remove_proc_entry(PROC_NAME, proc_entry_base);
	if (proc_entry_readonly != NULL)
			remove_proc_entry(PROC_NAME_READONLY, proc_entry_base);
	if (proc_entry_base != NULL)
			remove_proc_entry(PROC_NAME_BASE, NULL);
}

//  注册初始化Linux驱动的函数
module_init( proc_demo_init);
//  注册卸载Linux驱动的函数 
module_exit( proc_demo_exit);

