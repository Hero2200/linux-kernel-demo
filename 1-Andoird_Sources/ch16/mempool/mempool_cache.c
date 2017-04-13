#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/mempool.h>

static mempool_t *mempoolp;
struct data
{
	char *name;
	int value;
	int nr;

}*datap;

void *mempool_alloc_fun(gfp_t gfp_mask, void *pool_data)
{

	if (!mempoolp)
	{
		pool_data = kmalloc(sizeof(struct data), GFP_KERNEL);

		printk("alloc struct data\n");
	}
	else
	{
		if (mempoolp->curr_nr < mempoolp->min_nr)
		{
			void *element = mempoolp->elements[mempoolp->curr_nr];
			if (element)
			{
				((struct data*) element)->nr = mempoolp->curr_nr;
				mempoolp->elements[mempoolp->curr_nr--] = NULL;
			}
			return element;
		}
		else
			return NULL;

	}

	return pool_data;
}
void mempool_free_fun(void *element, void *pool_data)
{

	if (element)
	{
		kfree(element);
		printk("free struct data\n");

	}

}
static int __init demo_init(void)
{

	mempoolp = mempool_create(5, mempool_alloc_fun, mempool_free_fun, NULL);
	mempoolp->curr_nr = mempoolp->curr_nr - 1;

	datap = mempool_alloc(mempoolp, GFP_KERNEL);
	datap->name = "mempool data";
	datap->value = 4321;

	printk(KERN_ALERT "demo_init.\n");
	return 0;
}

static void __exit demo_exit(void)
{
	if (datap)
	{
		printk("data.name=%s\n", datap->name);
		printk("data.value=%d\n", datap->value);
		if (mempoolp && datap)
		{
			mempoolp->curr_nr = datap->nr;
			mempool_free(datap, mempoolp);
			mempoolp->curr_nr = mempoolp->min_nr;
			mempool_destroy(mempoolp);
		}

	}
	printk(KERN_ALERT "demo_exit.\n");
}
MODULE_LICENSE("GPL");
module_init(demo_init);
module_exit(demo_exit);
