#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <jni.h>
#include <leds_hal.h>

struct led_control_device_t *led_hal_device = NULL;

static jboolean led_setOn(JNIEnv* env, jobject thiz, jint led)
{
	LOGI("Led HAL JNI: led_setOn() is invoked.");

	if (led_hal_device == NULL)
	{
		LOGI("Led HAL JNI: led_hal_device was not fetched correctly.");
		return -1;
	}
	else
	{
		return led_hal_device->set_on(led_hal_device, led);
	}
}

static jboolean led_setOff(JNIEnv* env, jobject thiz, jint led)
{
	LOGI("Led HAL JNI: led_setOff() is invoked.");
	if (led_hal_device == NULL)
	{
		LOGI("Led HAL JNI: led_hal_device was not fetched correctly.");
		return -1;
	}
	else
	{
		return led_hal_device->set_off(led_hal_device, led);
	}
}

static inline int led_control_open(const struct hw_module_t* module,
        struct led_control_device_t** device)
{
	return module->methods->open(module, LED_HARDWARE_MODULE_ID,
	        (struct hw_device_t**) device);
}

static jboolean led_init(JNIEnv *env, jclass clazz)
{
	led_module_t* module;

	LOGE("**********start find hal *********");
	LOGE(LED_HARDWARE_MODULE_ID);

	if (hw_get_module(LED_HARDWARE_MODULE_ID, (const hw_module_t**) &module)
	        == 0)
	{
		LOGI("LedService JNI: LED Stub found.");
		if (led_control_open(&module->hw_module, &led_hal_device) == 0)
		{
			LOGI("LedService JNI: Got Stub operations.");
			return 0;
		}
	}

	LOGE("LedService JNI: Get Stub operations failed.");
	return -1;
}

static const JNINativeMethod methods[] =
{
{ "_init", "()Z", (void *) led_init },
{ "_set_on", "(I)Z", (void *) led_setOn },
{ "_set_off", "(I)Z", (void *) led_setOff }, };

int register_led_hal_jni(JNIEnv* env)
{
	static const char* const kClassName = "mobile/android/leds/hal/service/LedHalService";

	jclass clazz;

	clazz = env->FindClass(kClassName);
	if (clazz == NULL)
	{
		LOGE("Can't find class %s\n", kClassName);
		return -1;
	}
	if (env->RegisterNatives(clazz, methods,
	        sizeof(methods) / sizeof(methods[0])) != JNI_OK)
	{
		LOGE("Failed registering methods for %s\n", kClassName);
		return -1;
	}

	return 0;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = NULL;
	jint result = -1;

	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		LOGE("GetEnv failed!");
		return result;
	}

	register_led_hal_jni(env);

	return JNI_VERSION_1_4;
}

