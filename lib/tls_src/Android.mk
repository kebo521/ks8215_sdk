# Spreadtrum busmonitor hardware layer

LOCAL_PATH:= $(call my-dir)__

include $(CLEAR_VARS)
LOCAL_MODULE:= tls

#LOCAL_CFLAGS := -DSCX15 -I$(LOCAL_PATH)
LOCAL_SRC_FILES:= $(wildcard $(LOCAL_PATH)/library/*.c)
LOCAL_SRC_FILES+= $(wildcard $(LOCAL_PATH)/*.c)



LOCAL_C_INCLUDES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/.
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../

LOCAL_MODULE_TAGS:= optional

LOCAL_SHARED_LIBRARIES:= libc libcutils

NDK_APP_DST_DIR = $(LOCAL_PATH)/../tls/
include $(BUILD_SHARED_LIBRARY)


#include $(PREBUILT_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
#include $(PREBUILT_STATIC_LIBRARY)
