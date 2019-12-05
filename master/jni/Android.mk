LOCAL_PATH:= $(call my-dir)/..

 
# libtls.so
include $(CLEAR_VARS)
LOCAL_MODULE    := libtls
LOCAL_SRC_FILES += $(LOCAL_PATH)/../lib/tls/libtls.so
include $(PREBUILT_SHARED_LIBRARY)

# libsdk.so
include $(CLEAR_VARS)
LOCAL_MODULE    := libsdk
LOCAL_SRC_FILES += $(LOCAL_PATH)/../lib/sdk/libsdk.so
include $(PREBUILT_SHARED_LIBRARY)

# libgui.so
include $(CLEAR_VARS)
LOCAL_MODULE    := libgui
LOCAL_SRC_FILES += $(LOCAL_PATH)/../lib/gui/libgui.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE	:= master

#LOCAL_CFLAGS := -DSCX15 -I$(LOCAL_PATH)


LOCAL_SRC_FILES:= main.c app_show.c szzt_tms.c

LOCAL_C_INCLUDES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES +=\
	$(LOCAL_PATH)/. \
    $(LOCAL_PATH)/../lib \
	$(LOCAL_PATH)/../lib/tls \
	$(LOCAL_PATH)/../lib/sdk \
	$(LOCAL_PATH)/../lib/gui

#LOCAL_LDFLAGS += -L/$(LOCAL_PATH)/../lib/tls -ltls

LOCAL_SHARED_LIBRARIES:= libc libcutils libtls libsdk libgui

include $(BUILD_EXECUTABLE)
