#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/string.h>

extern const char* symbol_const;
extern int result;

extern int add(int x1, int x2);
extern int sub(int x1, int x2);


//  初始化Linux驱动
static int __init symbol_consumer_init(void)
{
    int x1 = 123;
    int x2 = 55;
    printk("symbol_consumer_init_success\n");
    printk("%d + %d = %d\n", x1, x2, add(x1, x2));
    printk("%d - %d = %d\n", x1, x2, sub(x1, x2));
    printk("result:%d\n", result);
    printk("const:%s\n", symbol_const);
    return 0;
}

// 卸载Linux驱动
static void __exit symbol_consumer_exit(void)
{
    //  输出日志信息
    printk("multi_file_driver_exit_success\n");


}

//  注册初始化Linux驱动的函数
module_init(symbol_consumer_init); 
//  注册卸载Linux驱动的函数
module_exit(symbol_consumer_exit);

MODULE_AUTHOR("lining");
MODULE_DESCRIPTION("multi file driver");
MODULE_ALIAS("multi file module.");
MODULE_LICENSE("GPL");

