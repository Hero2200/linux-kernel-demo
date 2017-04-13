#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-m.h>

#define DEVICE_NAME "s3c6410_leds"
#define DEVICE_COUNT 1               //  设备数量
#define S3C6410_LEDS_MAJOR 0  
#define S3C6410_LEDS_MINOR 234
#define PARAM_SIZE  3
static unsigned char mem[4]; // 保存4个Leds的设置状态
static int major = S3C6410_LEDS_MAJOR;
static int minor = S3C6410_LEDS_MINOR; 
static dev_t dev_number; //  设备号
static int leds_state = 1;
static char *params[] = {"string1", "string2","string3"};
static int param_size = PARAM_SIZE;

static struct class *leds_class = NULL;

static long s3c6410_leds_ioctl(struct file *filp, unsigned int cmd,
        unsigned long arg)
{

	switch (cmd)
	{
		unsigned tmp;

		case 0:
		case 1:
		if (arg > 4)
		{
			return -EINVAL;
		}
		tmp = ioread32(S3C64XX_GPMDAT);

		if (cmd == 1)
		{
			tmp &= (~(1 << arg));
		}
		else
		{
			tmp |= (1 << arg);
		}

		iowrite32(tmp, S3C64XX_GPMDAT);

		return 0;
		default:
		return -EINVAL;
	}
}
static ssize_t s3c6410_leds_write(struct file *file, const char __user *buf,
        size_t count, loff_t *ppos)
{

	unsigned tmp = count;
	unsigned long i = 0;
	memset(mem, 0, 4);

	if (count > 4)
	{
		tmp = 4;
	}

	if (copy_from_user(mem, buf, tmp))
	{
		return -EFAULT;
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			tmp = ioread32(S3C64XX_GPMDAT);
			if (mem[i] == '1')
			{
				tmp &= (~(1 << i));
			}
			else
			{
				tmp |= (1 << i);
			}

			iowrite32(tmp, S3C64XX_GPMDAT);

		}
		return count;
	}


}

static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .unlocked_ioctl = s3c6410_leds_ioctl, .write =
        s3c6410_leds_write };
static struct cdev leds_cdev;

//创建设备文件（/dev/s3c6410_leds）
static int leds_create_device(void)
{
	int ret = 0;
	int err = 0;

	//  初始化cdev的成员，并建立cdev和file_operations之间的连接
	cdev_init(&leds_cdev, &dev_fops);
	leds_cdev.owner = THIS_MODULE;
	if (major > 0)
	{
		//  获取设备号（主设备号和次设备号）
		dev_number = MKDEV(major, minor);
		err = register_chrdev_region(dev_number, DEVICE_COUNT, DEVICE_NAME);
		if (err < 0)
		{
			printk(KERN_WARNING "register_chrdev_region() failed\n");
			return err;
		}
	}
	else
	{
		err = alloc_chrdev_region(&leds_cdev.dev, 10, DEVICE_COUNT,
		        DEVICE_NAME);
		if (err < 0)
		{
			printk(KERN_WARNING "alloc_chrdev_region() failed\n");
			return err;
		}

		major = MAJOR(leds_cdev.dev);
		minor = MINOR(leds_cdev.dev);
		//dev_number = MKDEV(major, minor);
		dev_number = leds_cdev.dev;

	}
	ret = cdev_add(&leds_cdev, dev_number, DEVICE_COUNT);
	leds_class = class_create(THIS_MODULE, DEVICE_NAME);
	device_create(leds_class, NULL, dev_number, NULL, DEVICE_NAME);

	return ret;
}

static void leds_init_gpm(int leds_default)
{
	int tmp = 0;
	//  初始化端口配置寄存器
	tmp = ioread32(S3C64XX_GPMCON);
	tmp &= (~0xFFFF);
	tmp |= 0x1111; // 0001000100010001
	iowrite32(tmp, S3C64XX_GPMCON);

	//  初始化端口上拉电路寄存器
	tmp = ioread32(S3C64XX_GPMPUD);
	tmp &= (~0xFF);
	tmp |= 0xAA; // 01010101
	iowrite32(tmp, S3C64XX_GPMPUD);

	//  初始化端口数据寄存器
	tmp = ioread32(S3C64XX_GPMDAT);
	tmp &= (~0xF);
	tmp |= leds_default;
	iowrite32(tmp, S3C64XX_GPMDAT);
}

//  初始化LED驱动
static int leds_init(void)
{
	int ret;
	ret = leds_create_device();
	leds_init_gpm(~leds_state);
	printk(DEVICE_NAME"\tinitialized\n");

	printk("param0\t%s\n", params[0]);
	printk("param1\t%s\n", params[1]);
	printk("param2\t%s\n", params[2]);

	return ret;
}
static void leds_destroy_device(void)
{
	device_destroy(leds_class, dev_number);

	if (leds_class)
		class_destroy(leds_class);
	unregister_chrdev_region(dev_number, DEVICE_COUNT);

	return;

}
static void leds_exit(void)
{
	leds_destroy_device();
	printk(DEVICE_NAME"\texit!\n");
}

module_init(leds_init);
module_exit(leds_exit);
module_param(leds_state, int, S_IRUGO|S_IWUSR);
module_param_array(params, charp, &param_size, S_IRUGO|S_IWUSR);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lining");
