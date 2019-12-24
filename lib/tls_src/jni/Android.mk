# Spreadtrum busmonitor hardware layer

LOCAL_PATH:= $(call my-dir)/..

#APP_ABI := armeabi-v7a

include $(CLEAR_VARS)
LOCAL_MODULE:= tls

#LOCAL_CFLAGS += -fvisibility=hidden
#LOCAL_CFLAGS += -fPIC -fpic
#LOCAL_CFLAGS := -DSCX15 -I$(LOCAL_PATH)
LOCAL_CFLAGSLOCAL_CFLAGS = -Wno-psabi

# fix compiler:-Werror=format-security
#LOCAL_DISABLE_FORMAT_STRING_CHECKS := true

LOCAL_SRC_FILES:= $(wildcard $(LOCAL_PATH)/*.c)
LOCAL_SRC_FILES+= $(wildcard $(LOCAL_PATH)/library/*.c)

LOCAL_C_INCLUDES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/.
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../

#LOCAL_MODULE_TAGS:= optional

#LOCAL_SHARED_LIBRARIES:= libc

NDK_APP_DST_DIR = $(LOCAL_PATH)/../tls/


include $(BUILD_SHARED_LIBRARY)


#include $(PREBUILT_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
#include $(PREBUILT_STATIC_LIBRARY)
