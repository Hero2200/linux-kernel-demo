LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_SRC_FILES := leds_hal.c
LOCAL_MODULE :=led_hal.default
LOCAL_MODULE_TAGS := eng  
include $(BUILD_SHARED_LIBRARY)
     

 

    
  


   

  


