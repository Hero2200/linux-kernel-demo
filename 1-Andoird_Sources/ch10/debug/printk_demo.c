#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#if 1
  #define print_debug(x,...) printk(x,##__VA_ARGS__)
#else
  #define print_debug(x,...)  do {} while(0)
#endif

//  初始化Linux驱动
static int __init printk_demo_init(void)
{
    int i = 0;

    for(; i < 8; i++)
        //printk("<%d><%d>%s\n", i, i, __FUNCTION__);
        print_debug("<%d>d<%d>%s\n", i, i, __FUNCTION__);
	return 0;

}

// 卸载Linux驱动
static void __exit printk_demo_exit(void)
{
    int i = 0;
    for(; i < 8; i++)
        // printk("<%d><%d>%s\n", i, i, __FUNCTION__);
	print_debug("<%d><%d>%s\n", i, i, __FUNCTION__);
}

//  注册初始化Linux驱动的函数
module_init( printk_demo_init); 
//  注册卸载Linux驱动的函数 
module_exit(  printk_demo_exit);


