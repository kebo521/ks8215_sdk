LOCAL_PATH := $(call my-dir)

# libsdk.so
include $(CLEAR_VARS)
LOCAL_MODULE    := libsdk
LOCAL_SRC_FILES += $(LOCAL_PATH)/../sdk/libsdk.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := libgui


#graphics_adf.c graphics_fbdev.c xui_afb.c
LOCAL_SRC_FILES := graphics_adf.c graphics_fbdev.c xui_afb.c xui_ui.c xui_font.c xui_gui.c \
                   ui_menu.c QR_Encode.c language.c input_hand_arm.c EvenMsg.c

LOCAL_C_INCLUDES +=\
	$(LOCAL_PATH)/ \
    $(LOCAL_PATH)/../ \
    external/libpng \
    external/zlib \
    external/freetype/include \
	system/core/adf/libadf/include
#system/core/libpixelflinger/include

LOCAL_WHOLE_STATIC_LIBRARIES += libadf

LOCAL_SHARED_LIBRARIES:= libcutils libdl libsdk

LOCAL_STATIC_LIBRARIES:= libpng libz
  
#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

# This used to compare against values in double-quotes (which are just
# ordinary characters in this context).  Strip double-quotes from the
# value so that either will work.

ifeq ($(subst ",,$(TARGET_RECOVERY_PIXEL_FORMAT)),RGBX_8888)
  LOCAL_CFLAGS += -DRECOVERY_RGBX
endif
ifeq ($(subst ",,$(TARGET_RECOVERY_PIXEL_FORMAT)),BGRA_8888)
  LOCAL_CFLAGS += -DRECOVERY_BGRA
endif

ifeq ($(strip $(SDGUI_MULTI_LANGUAGE_SUPPORT)),true)
LOCAL_CFLAGS += -DMULTI_LANGUAGE_SUPPORT
endif

# Define in file : sl8521ett_3h10_base.mk
ifeq ($(strip $(SDGUI_BITMAP_FONT_SUPPORT)),true)
LOCAL_CFLAGS += -DBITMAP_FONT_SUPPORT
endif


ifneq ($(TARGET_RECOVERY_OVERSCAN_PERCENT),)
  LOCAL_CFLAGS += -DOVERSCAN_PERCENT=$(TARGET_RECOVERY_OVERSCAN_PERCENT)
else
  LOCAL_CFLAGS += -DOVERSCAN_PERCENT=0
endif

NDK_APP_DST_DIR = $(LOCAL_PATH)/../gui/

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)
