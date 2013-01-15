LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gtest_static

LOCAL_MODULE_FILENAME := libgtest

LOCAL_SRC_FILES := src/gtest-all.cc

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/gtest/internal \
                    $(LOCAL_PATH)/include
                
include $(BUILD_STATIC_LIBRARY)