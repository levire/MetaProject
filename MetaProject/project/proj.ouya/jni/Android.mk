LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_CFLAGS +=  -DOUYA=1 -DCOCOS2D_DEBUG=1

NORMAL_SRC_FILES := \
    hellocpp/main.cpp \
    ../../Classes/AppDelegate.cpp \
    ../../Classes/HelloWorldScene.cpp

TEST_SRC_FILES := \
    hellocpp/main.cpp \
    ../../Tests/AppDelegate.cpp \
    ../../Tests/TestRunnerScene.cpp \
    ../../Tests/SampleTest.cpp \
    ../../Tests/CocosUnitTestResultPrinter.cpp

ifeq ($(BUILD_TESTS), true)
    LOCAL_SRC_FILES := $(TEST_SRC_FILES)
else    
    LOCAL_SRC_FILES := $(NORMAL_SRC_FILES)
endif                  

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

ifeq ($(BUILD_TESTS), true)
    LOCAL_WHOLE_STATIC_LIBRARIES += gtest_static
endif

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx/platform/ouya)
$(call import-module,extensions/ouya)

ifeq ($(BUILD_TESTS), true)
    $(call import-module,gtest)
endif