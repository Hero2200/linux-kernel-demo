#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-m.h>

#define DEVICE_NAME "s3c6410_leds_hal"
#define DEVICE_COUNT 1               //  设备数量
#define S3C6410_LEDS_MAJOR 0
#define S3C6410_LEDS_MINOR 234


