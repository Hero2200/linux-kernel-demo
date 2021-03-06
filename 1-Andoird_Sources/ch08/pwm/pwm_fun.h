#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <mach/map.h>  
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-f.h>
#include <mach/gpio-bank-k.h>

#define DEVICE_NAME     "pwm_dev"

#define PWM_IOCTL_START		1
#define PWM_IOCTL_STOP		0

extern void pwm_start(void);
extern void pwm_stop(void);
