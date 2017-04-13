#include "leds_hal.h"
#include "../leds_hal_define.h"

int dev_file = 0;

//  on_off: 1表示开，0表示关
int led_on_off(struct led_control_device_t *dev, int32_t led, int32_t on_off)
{
	if (led >= 0 && led <= 3)
	{

		if (on_off == 1)  
			LOGI("LED Stub:set %d on", led);
		else
			LOGI("LED Stub:set %d off", led);
		unsigned char buf[5];
		buf[0] = S3C6410_LEDS_HAI_READ_GPMDAT;
		write(dev_file, buf, 5);
		read(dev_file, buf, 5);
		buf[0] = S3C6410_LEDS_HAI_WRITE_GPMDAT; // 修改GPMDAT寄存器的值
		switch (led)
		{
			case 0:
			if (on_off == 1) // 打开
				buf[4] &= 0xFE; // 11111110
			else if (on_off == 0) //  关闭
				buf[4] |= 0x1; //  00000001
				break;
			case 1:
			if (on_off == 1) // 打开
			{
				buf[4] &= 0xFD; // 11111101

			}
			else if (on_off == 0) //  关闭
			{

				buf[4] |= 0x2; //  00000010
			}
				break;
			case 2:
			if (on_off == 1) // 打开
				buf[4] &= 0xFB; // 11111011
			else if (on_off == 0) //  关闭
				buf[4] |= 0x4; //  00000100

				break;
			case 3:
			if (on_off == 1) // 打开
				buf[4] &= 0xF7; // 11110111
			else if (on_off == 0) //  关闭
				buf[4] |= 0x8; //  00001000
				break;
		}
		write(dev_file, buf, 5);

	}
	else
	{
		LOGI("LED Stub: set led %d on error,no this led", led);
	}

	return 0;

}

int led_on(struct led_control_device_t *dev, int32_t led)
{
	return led_on_off(dev, led, 1);
}

int led_off(struct led_control_device_t *dev, int32_t led)
{

	return led_on_off(dev, led, 0);
}
int led_device_close(struct hw_device_t* device)
{
	struct led_control_device_t* ctx = (struct led_control_device_t*) device;
	if (ctx)
	{
		free(ctx);
	}
	close(dev_file);
	return 0;
}
static void leds_init_gpm()
{
	int tmp = 0;
	//  初始化端口配置寄存器

	unsigned char buf[5];
	buf[0] = S3C6410_LEDS_HAI_READ_GPMCON;
	write(dev_file, buf, 5);
	read(dev_file, buf, 5);
	buf[3] |= 0x11;
	buf[4] |= 0x11;
	buf[0] = S3C6410_LEDS_HAI_WRITE_GPMCON;
	write(dev_file, buf, 5);

	//  初始化端口上拉电路寄存器
	buf[0] = S3C6410_LEDS_HAI_READ_GPMPUD;
	write(dev_file, buf, 5);
	read(dev_file, buf, 5);
	buf[4] |= 0xAA;
	buf[0] = S3C6410_LEDS_HAI_WRITE_GPMPUD;
	write(dev_file, buf, 5);

}
static int led_device_open(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device)
{
	struct led_control_device_t *dev;
	dev = (struct led_control_device_t *) malloc(sizeof(*dev));
	memset(dev, 0, sizeof(*dev));

	dev->hw_device.tag = HARDWARE_DEVICE_TAG;
	dev->hw_device.version = 0;
	dev->hw_device.module = (struct hw_module_t*) module;
	dev->hw_device.close = led_device_close;

	dev->set_on = led_on;
	dev->set_off = led_off;

	//*device = &dev->hw_device;
	*device = (hw_device_t*)dev;

	dev_file = open("/dev/s3c6410_leds_hal", O_RDWR);
	if (dev_file < 0)
	{
		LOGI("LED Stub: open /dev/s3c6410_leds_hal  fail.");
	}
	else
	{
		LOGI("LED Stub: open /dev/s3c6410_leds_hal success .");
	}
	leds_init_gpm();
	return 0;
}

static struct hw_module_methods_t led_module_methods =
{ open: led_device_open };

struct led_module_t HAL_MODULE_INFO_SYM =
{ hw_module:
{ tag: HARDWARE_MODULE_TAG, version_major: 1, version_minor: 0, id
: LED_HARDWARE_MODULE_ID,
name: "Sample LED HAL Stub",
author: "Lining",
methods: &led_module_methods,
}

};

/*struct hw_module_t HAL_MODULE_INFO_SYM =
{ tag: HARDWARE_MODULE_TAG, version_major: 1, version_minor: 0, id
: LED_HARDWARE_MODULE_ID,
name: "Sample LED HAL Stub",
author: "Lining",
methods: &led_module_methods,

};*/


