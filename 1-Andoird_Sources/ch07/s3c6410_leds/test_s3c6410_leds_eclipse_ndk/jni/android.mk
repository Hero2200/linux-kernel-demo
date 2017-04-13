LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ndk_test_s3c6410_leds
LOCAL_SRC_FILES := ndk_test_s3c6410_leds.c

include $(BUILD_SHARED_LIBRARY)
  