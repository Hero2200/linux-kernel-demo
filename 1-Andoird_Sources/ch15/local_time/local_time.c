#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

static int __init demo_init(void)
{
	struct timeval tv;
	struct timespec ts;
        ts.tv_nsec = 0;
        ts.tv_sec = (unsigned long) mktime (2009, 9, 28, 17, 55, 30);
	do_gettimeofday(&tv);

	printk("sec:%ld, nsec:%ld\n", tv.tv_sec, tv.tv_usec);
	printk("setting success:%d\n", do_settimeofday(&ts));
	printk("demo_init.\n");
	return 0;  
}    

static void __exit demo_exit(void)
{

	printk("demo_exit.\n");
}
MODULE_LICENSE("GPL");
module_init( demo_init);
module_exit( demo_exit);
