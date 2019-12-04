# Spreadtrum busmonitor hardware layer

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -lpthread 
  
#LOCAL_CFLAGS := -DSCX15 -I$(LOCAL_PATH)
LOCAL_SRC_FILES:= sys_sdk.c esm_sdk.c

LOCAL_MODULE:= libsdk

LOCAL_SHARED_LIBRARIES:= libc libcutils

LOCAL_C_INCLUDES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES +=\
	$(LOCAL_PATH)/. \
    $(LOCAL_PATH)/../

LOCAL_MODULE_TAGS:= optional

include $(BUILD_SHARED_LIBRARY)
