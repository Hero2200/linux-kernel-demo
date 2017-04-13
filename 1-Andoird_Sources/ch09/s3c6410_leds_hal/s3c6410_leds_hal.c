#include "s3c6410_leds_hal.h"
#include "leds_hal_define.h"

static unsigned char mem[5]; // 第1个字节：GPM寄存器类型，后面4个字节保存GPM寄存器的值
static int major = S3C6410_LEDS_MAJOR;
static int minor = S3C6410_LEDS_MINOR;
static dev_t dev_number; //  设备号
static struct class *leds_class = NULL;
  
//  只处理从start开始的4个字节,第start个字节为int的最高位
static int bytes_to_int(unsigned char buf[], int start)
{
	int n = 0;
	n = ((int) buf[start]) << 24 | ((int) buf[start + 1]) << 16
	        | ((int) buf[start + 2]) << 8 | ((int) buf[start + 3]);
	return n;
}

static void int_to_bytes(int n, unsigned char buf[], int start)
{
	buf[start] = n >> 24;
	buf[start + 1] = n >> 16;
	buf[start + 2] = n >> 8;
	buf[start + 3] = n;
}
//  向GPM寄存器写数据
static ssize_t s3c6410_leds_hal_write(struct file *file, const char __user *buf,
        size_t count, loff_t *ppos)
{

	if (copy_from_user(mem, buf, 5))
	{
		return -EFAULT;
	}
	else
	{
		int gpm_type = mem[0]; //  获取GPM寄存器类型
		switch (gpm_type)
		{
			case S3C6410_LEDS_HAI_WRITE_GPMCON:
				iowrite32(bytes_to_int(mem, 1), S3C64XX_GPMCON);
				break;
			case S3C6410_LEDS_HAI_WRITE_GPMPUD:
				iowrite32(bytes_to_int(mem, 1), S3C64XX_GPMPUD);
				break;
			case S3C6410_LEDS_HAI_WRITE_GPMDAT:
				iowrite32(bytes_to_int(mem, 1), S3C64XX_GPMDAT);
				break;
		}

	}
	return 5;
}

//  向GPM寄存器写数据
static ssize_t s3c6410_leds_hal_read(struct file *file, char __user *buf,
        size_t count, loff_t *ppos)
{
	int gpm_type = mem[0]; //  获取GPM寄存器类型
	int gpm_value = 0;

	switch (gpm_type)
	{
		case S3C6410_LEDS_HAI_READ_GPMCON:
			gpm_value = ioread32(S3C64XX_GPMCON);
			break;
		case S3C6410_LEDS_HAI_READ_GPMPUD:
			gpm_value = ioread32(S3C64XX_GPMPUD);
			break;
		case S3C6410_LEDS_HAI_READ_GPMDAT:

			gpm_value = ioread32(S3C64XX_GPMDAT);
			break;
	}
	int_to_bytes(gpm_value, mem, 1);
	if (copy_to_user(buf, (void*) mem, 5))
	{
		return -EFAULT;
	}
	return 5;
}

static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .read = s3c6410_leds_hal_read, .write =
        s3c6410_leds_hal_write };
static struct cdev leds_cdev;

//创建设备文件（/dev/s3c6410_leds_hal）
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

//  初始化LED驱动
static int leds_init(void)
{
	int ret;
	ret = leds_create_device();
	printk(DEVICE_NAME"\tinitialized\n");
	printk(KERN_EMERG"tes1fdddfs1t\n");
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
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lining");
