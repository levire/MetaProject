LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gmock_static

LOCAL_MODULE_FILENAME := libgmock

LOCAL_SRC_FILES := src/gmock-all.cc

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/gmock/internal \
                    $(LOCAL_PATH)/include

LOCAL_WHOLE_STATIC_LIBRARIES += gtest_static                

include $(BUILD_STATIC_LIBRARY)

$(call import-module,gmock/gtest)