# Android.mk
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE:= led_hal_jni

LOCAL_MODULE_PATH := /root/drivers/s3c6410_leds_hal/leds_hal_jni

LOCAL_SRC_FILES:= LedHalService.cpp
   

LOCAL_SHARED_LIBRARIES := \
	libandroid_runtime \
	libcutils \
	libhardware \
	libhardware_legacy \
	libnativehelper \
        libsystem_server \
	libutils \
	libui \
        libsurfaceflinger_client
       
  
LOCAL_C_INCLUDES += \
	$(JNI_H_INCLUDE) \
        hardware/leds_hal

LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)


    
