#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <asm-generic/local.h>

static char* module_address = "";

void force(void)
{
}
int __init force_kill_driver_init(void)
{
	if (strcmp(module_address, "") != 0)
	{
		char *temp;
		long address =simple_strtol(module_address, &temp, 16);
		struct module *mod = (struct module*)address;

		mod->state = MODULE_STATE_LIVE;
		mod->refptr = NULL;
		mod->exit = force;
		//module_put(mod);
	}
	return 0;
}
void __exit force_kill_driver_exit(void)
{
}

module_init(force_kill_driver_init);
module_exit(force_kill_driver_exit);

module_param(module_address, charp, S_IRUGO | S_IWUSR);

MODULE_LICENSE("GPL");
