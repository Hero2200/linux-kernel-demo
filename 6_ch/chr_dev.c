/*
 * =====================================================================================
 *       Filename:  chr_dev.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017年04月01日 14时55分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *   Organization:  
 * =====================================================================================
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#define printf printk

static int __init demo_init(void)
{

	printf ( "--liuj demo_init\n" );

	return 0;
}

static void __exit demo_exit(void)
{

	printf ( "--liuj demo_exit\n" );
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
