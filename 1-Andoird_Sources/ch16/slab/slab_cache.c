#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/slab.h>

static struct kmem_cache *cachep;
struct data
{
	char *name;
	int value;

} *datap;

static int __init demo_init(void)
{
	cachep = kmem_cache_create("slab_test", sizeof(struct data), 0, SLAB_HWCACHE_ALIGN | SLAB_PANIC, NULL);
	datap = kmem_cache_alloc(cachep, GFP_KERNEL);
	datap->name = "slab data";
	datap->value = 1234;
	printk(KERN_ALERT "demo_init.\n");
	return 0;
}

static void __exit demo_exit(void)
{
    if(datap)
    {
    	printk("data.name=%s\n", datap->name);
    	printk("data.value=%d\n", datap->value);
    	kmem_cache_free(cachep, datap);
    	kmem_cache_destroy(cachep);
    }
	printk(KERN_ALERT "demo_exit.\n");
}
MODULE_LICENSE("GPL");
module_init(demo_init);
module_exit(demo_exit);
