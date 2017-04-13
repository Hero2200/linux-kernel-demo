#include "pwm_fun.h"
static struct semaphore lock;
static int s3c64xx_pwm_open(struct inode *inode, struct file *file)
{
	if (!down_trylock(&lock))
		return 0;
	else   
		return -EBUSY;
}
static int s3c64xx_pwm_close(struct inode *inode, struct file *file)
{
	up(&lock);
	return 0;
}
static long s3c64xx_pwm_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{

	switch (cmd) {
		case PWM_IOCTL_START:
			
			pwm_start();
			break;

		case PWM_IOCTL_STOP:
		default:
			pwm_stop();
			break;
	}

	return 0;
}


static struct file_operations dev_fops = {
    .owner			= THIS_MODULE,
    .open			= s3c64xx_pwm_open,
    .release		= s3c64xx_pwm_close, 
    .unlocked_ioctl	= s3c64xx_pwm_ioctl,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int __init dev_init(void)
{
	int ret;

	init_MUTEX(&lock);
	ret = misc_register(&misc);

	printk (DEVICE_NAME"\tinitialized\n");
    	return ret;
}

static void __exit dev_exit(void)
{
	misc_deregister(&misc);
}
module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lining");
MODULE_DESCRIPTION("PWM Driver");
