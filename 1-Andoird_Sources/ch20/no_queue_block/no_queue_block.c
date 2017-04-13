#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/timer.h>
#include <linux/types.h>	/* size_t */
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/hdreg.h>	/* HDIO_GETGEO */
#include <linux/kdev_t.h>
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/buffer_head.h>	/* invalidate_bdev */
#include <linux/bio.h>
#include <linux/version.h>


#define BLOCK_DEV_DEVICEMAJOR        COMPAQ_SMART2_MAJOR
#define BLOCK_DEV_DISKNAME        "no_queue_block"
#define BLOCK_DEV_BYTES        (1*1024*1024)

static struct request_queue *block_dev_queue;
static struct gendisk *block_dev_disk;  
unsigned char block_dev_data[BLOCK_DEV_BYTES];

static int block_dev_make_request(struct request_queue *q, struct bio *bio)
{
        struct bio_vec *bvec;
        int i;
        void *dsk_mem;

        if ((bio->bi_sector << 9) + bio->bi_size > BLOCK_DEV_BYTES) {
                printk(KERN_ERR BLOCK_DEV_DISKNAME
                        ": bad request: block=%llu, count=%u\n",
                        (unsigned long long)bio->bi_sector, bio->bi_size);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
                bio_endio(bio, 0, -EIO);
#else
                bio_endio(bio, -EIO);
#endif
                return 0;
        }

        dsk_mem = block_dev_data + (bio->bi_sector << 9);

        bio_for_each_segment(bvec, bio, i) {
                void *iovec_mem;

                switch (bio_rw(bio)) {
                case READ:
                case READA:
                        iovec_mem = kmap(bvec->bv_page) + bvec->bv_offset;
                        memcpy(iovec_mem, dsk_mem, bvec->bv_len);
                        kunmap(bvec->bv_page);
                        break;
                case WRITE:
                        iovec_mem = kmap(bvec->bv_page) + bvec->bv_offset;
                        memcpy(dsk_mem, iovec_mem, bvec->bv_len);
                        kunmap(bvec->bv_page);
                        break;
                default:
                        printk(KERN_ERR BLOCK_DEV_DISKNAME
                                ": unknown value of bio_rw: %lu\n",
                                bio_rw(bio));
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
                        bio_endio(bio, 0, -EIO);
#else
                        bio_endio(bio, -EIO);
#endif
                        return 0;
                }
                dsk_mem += bvec->bv_len;
        }

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
        bio_endio(bio, bio->bi_size, 0);
#else
        bio_endio(bio, 0);
#endif

        return 0;
}


struct block_device_operations block_dev_fops = {
        .owner                = THIS_MODULE,
};

static int __init block_dev_init(void)
{
        int ret;

        block_dev_queue = blk_alloc_queue(GFP_KERNEL);
        if (!block_dev_queue) {
                ret = -ENOMEM;
                goto err_alloc_queue;
        }
        blk_queue_make_request(block_dev_queue, block_dev_make_request);

        block_dev_disk = alloc_disk(1);
        if (!block_dev_disk) {
                ret = -ENOMEM;
                goto err_alloc_disk;
        }

        strcpy(block_dev_disk->disk_name, BLOCK_DEV_DISKNAME);
        block_dev_disk->major = BLOCK_DEV_DEVICEMAJOR;
        block_dev_disk->first_minor = 0;
        block_dev_disk->fops = &block_dev_fops;
        block_dev_disk->queue = block_dev_queue;
        set_capacity(block_dev_disk, BLOCK_DEV_BYTES>>9);
        add_disk(block_dev_disk);

        return 0;

err_alloc_disk:
        blk_cleanup_queue(block_dev_queue);
err_alloc_queue:
        return ret;
}


static void __exit block_dev_exit(void)
{
        del_gendisk(block_dev_disk);
        put_disk(block_dev_disk);
        blk_cleanup_queue(block_dev_queue);
}

module_init(block_dev_init);
module_exit(block_dev_exit);
