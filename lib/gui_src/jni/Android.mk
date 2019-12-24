LOCAL_PATH := $(call my-dir)/..

# libsdk.so
include $(CLEAR_VARS)
LOCAL_MODULE    := libsdk
LOCAL_SRC_FILES += $(LOCAL_PATH)/../sdk/libsdk.so
include $(PREBUILT_SHARED_LIBRARY)

# libsdk.so
include $(CLEAR_VARS)
LOCAL_MODULE    := libuiadf
LOCAL_SRC_FILES += $(LOCAL_PATH)/libuiadf.so
include $(PREBUILT_SHARED_LIBRARY)
#PREBUILT_STATIC_LIBRARY


include $(CLEAR_VARS)
LOCAL_MODULE := libgui


#graphics_adf.c graphics_fbdev.c xui_afb.c
LOCAL_SRC_FILES := xui_ui.c xui_font.c xui_gui.c \
                   ui_menu.c QR_Encode.c language.c input_hand_arm.c EvenMsg.c


LOCAL_C_INCLUDES +=\
	$(LOCAL_PATH)/ \
	$(LOCAL_PATH)/../ 

#LOCAL_WHOLE_STATIC_LIBRARIES += libadf

LOCAL_SHARED_LIBRARIES:= libsdk libuiadf

LOCAL_STATIC_LIBRARIES:= libevent 
  
#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

# This used to compare against values in double-quotes (which are just
# ordinary characters in this context).  Strip double-quotes from the
# value so that either will work.

NDK_APP_DST_DIR = $(LOCAL_PATH)/../gui/

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)
