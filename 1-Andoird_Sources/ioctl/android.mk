LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= test_ioctl.c

LOCAL_MODULE := ioctl
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE) 
#include $(BUILD_SHARED_LIBRARY) 
#include $(BUILD_STATIC_LIBRARY) 
  
