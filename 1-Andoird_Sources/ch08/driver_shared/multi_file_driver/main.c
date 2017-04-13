#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include "product.h"  

extern int add(int x1, int x2);


//  初始化Linux驱动
static int __init main_init(void)
{
    int x1 = 20;
    int x2 = 68;
    printk("<1>multi_file_driver_main_init_success\n");
    printk("%d + %d = %d\n", x1, x2, add(x1, x2));
    printk("Product Name:%s\n", get_product_name());
    return 0;
}

// 卸载Linux驱动
static void __exit main_exit(void)
{
    //  输出日志信息
    printk("multi_file_driver_exit_success\n");


}

//  注册初始化Linux驱动的函数
module_init(main_init); 
//  注册卸载Linux驱动的函数
module_exit(main_exit);

MODULE_AUTHOR("lining");
MODULE_DESCRIPTION("multi file driver");
MODULE_ALIAS("multi file module.");
MODULE_LICENSE("GPL");
