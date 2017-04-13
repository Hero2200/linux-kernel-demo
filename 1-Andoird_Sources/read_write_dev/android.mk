LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= rw_dev.c

LOCAL_MODULE := rwdev
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE) 
#include $(BUILD_SHARED_LIBRARY) 
#include $(BUILD_STATIC_LIBRARY) 
  
