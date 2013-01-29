LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_CFLAGS +=  -DOUYA=1 -DCOCOS2D_DEBUG=1

ifeq ($(BUILD_TESTS), true)
    include $(LOCAL_PATH)/../../Tests/Android.mk
else
    include $(LOCAL_PATH)/../../Classes/Android.mk    
endif                  

LOCAL_SRC_FILES += hellocpp/main.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static

ifeq ($(BUILD_TESTS), true)
    LOCAL_WHOLE_STATIC_LIBRARIES += gmock_static
    LOCAL_WHOLE_STATIC_LIBRARIES += gtest_static
endif

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx/platform/ouya)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions/ouya)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)

ifeq ($(BUILD_TESTS), true)
    $(call import-module,gmock/)
    $(call import-module,gmock/gtest)
endif