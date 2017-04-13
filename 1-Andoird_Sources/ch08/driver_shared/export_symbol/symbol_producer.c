#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

static const char* symbol_const = "被导出的常量";
static int result = 0;  

static int add(int x1, int x2)
{  
    return x1 + x2;
}
static int sub(int x1, int x2)
{
    return x1 - x2;
}

//  初始化Linux驱动
static int __init symbol_producer_init(void)
{
    int x1 = 88;
    int x2 = 20;
    printk("symbol_producer_init_success\n");
    printk("%d + %d = %d\n", x1, x2, add(x1, x2));
    printk("%d - %d = %d\n", x1, x2, sub(x1, x2));
    result = add(x1, x2) + sub(x1, x2);
    return 0;
}

// 卸载Linux驱动
static void __exit symbol_producer_exit(void)
{
    //  输出日志信息
    printk("symbol_producer_exit_success\n");
}

//  注册初始化Linux驱动的函数
module_init(symbol_producer_init); 
//  注册卸载Linux驱动的函数
module_exit(symbol_producer_exit);

EXPORT_SYMBOL(add);
EXPORT_SYMBOL(result);
EXPORT_SYMBOL_GPL(sub);
EXPORT_SYMBOL_GPL(symbol_const);

MODULE_AUTHOR("lining");
MODULE_DESCRIPTION("multi file driver");
MODULE_ALIAS("multi file module.");
MODULE_LICENSE("GPL");
