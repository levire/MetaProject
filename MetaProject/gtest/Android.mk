LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gtest

LOCAL_MODULE_FILENAME := libgtest

LOCAL_SRC_FILES := \
    src/gtest_main.cc \
    src/gtest-all.cc \
    src/gtest-death-test.cc \
    src/gtest-filepath.cc \
    src/gtest-internal-inl.h \
    src/gtest-port.cc \
    src/gtest-printers.cc \
    src/gtest-test-part.cc \
    src/gtest-typed-test.cc \
    src/gtest.cc

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/gtest/internal
                
include $(BUILD_STATIC_LIBRARY)