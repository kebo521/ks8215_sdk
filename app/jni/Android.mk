LOCAL_PATH:= $(call my-dir)/..

 
# libtls.so
include $(CLEAR_VARS)
LOCAL_MODULE    := libtls
LOCAL_SRC_FILES += $(LOCAL_PATH)/../lib/tls/libtls.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE	:= ksmain

#LOCAL_CFLAGS := -DSCX15 -I$(LOCAL_PATH)


LOCAL_SRC_FILES:= app_main.c

LOCAL_C_INCLUDES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES +=\
	$(LOCAL_PATH)/. \
    $(LOCAL_PATH)/../lib \
	$(LOCAL_PATH)/../lib/tls

#LOCAL_LDFLAGS += -L/$(LOCAL_PATH)/../lib/tls -ltls

LOCAL_SHARED_LIBRARIES:= libc libcutils libtls
include $(BUILD_EXECUTABLE)
