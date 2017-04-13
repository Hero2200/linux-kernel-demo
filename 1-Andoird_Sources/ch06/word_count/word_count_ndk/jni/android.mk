LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ndk_test_word_count
LOCAL_SRC_FILES := ndk_test_word_count.c

include $(BUILD_SHARED_LIBRARY)
  