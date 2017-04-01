/*
 * =====================================================================================
 *       Filename:  1-module_param.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017年03月29日 11时28分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *   Organization:  
 * =====================================================================================
 */

#include <linux/kernel>
#include <linux/module.h>
#include <linux/init.h>
#define printf printk
static char *book_name = "this is liuijiang Book";
module_param(boo_name,charp,S_IRUGO);

static int __init demo_init(void)
{

	printf ( "Hellow kernel ..%s\n",__func__ );
	printf ( "book_name = %s\n",book_name );

	return 0;
}

static void __exit demo_exit(void)
{
	printf ( "Good baby kernel\n" );
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Liujiang");
MODULE_DESCRIPTION("A simple kernel.ko");
