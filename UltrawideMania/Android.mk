LOCAL_PATH := $(call my-dir)
MOD_PATH := $(LOCAL_PATH)
include $(CLEAR_VARS)

# Change this or pass to ndk-build manually
MOD_NAME := UltrawideMania

LOCAL_MODULE := $(MOD_NAME)

LOCAL_C_INCLUDES := \
	$(MOD_PATH)/GameAPI/C \
    $(MOD_PATH)/$(MOD_NAME) \
    $(MOD_PATH)/$(MOD_NAME)/Objects

LOCAL_SRC_FILES := \
    $(MOD_PATH)/GameAPI/C/GameAPI/Game.c \
    $(MOD_PATH)/$(MOD_NAME)/dllmain.c \
    $(MOD_PATH)/$(MOD_NAME)/Objects/All.c

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
