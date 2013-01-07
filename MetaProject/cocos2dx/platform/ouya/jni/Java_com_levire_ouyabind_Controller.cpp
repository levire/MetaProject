#include "JniHelper.h"
#include <jni.h>
#include "Java_com_levire_ouyabind_Controller.h"
#include "platform/CCCommon.h"

using namespace cocos2d;

extern "C"
{
	jobject getOuyaControllerByPlayer(int playerNum)
	{
		JniMethodInfo methodInfo;
		bool isMethodAvailable = JniHelper::getStaticMethodInfo(
									methodInfo,
								   	"com/levire/ouyabind/OuyaBindController",
								   	"getControllerByPlayer",
								   	"(I)Ltv/ouya/console/api/OuyaController;");

		if (isMethodAvailable)
		{
			jobject ouyaController = methodInfo.env->CallStaticObjectMethod(methodInfo.classID,
                                                                            methodInfo.methodID,
                                                                            playerNum);
            
			methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return ouyaController;
		}
        return NULL;
	}
    
    jobject getOuyaControllerByDeviceId(int deviceId)
    {
        JniMethodInfo methodInfo;
		bool isMethodAvailable = JniHelper::getStaticMethodInfo(
                                                                methodInfo,
                                                                "com/levire/ouyabind/OuyaBindController",
                                                                "getControllerByDeviceId",
                                                                "(I)Ltv/ouya/console/api/OuyaController;");
        
		if (isMethodAvailable)
		{
			jobject ouyaController = methodInfo.env->CallStaticObjectMethod(methodInfo.classID,
                                                                            methodInfo.methodID,
                                                                            deviceId);
            
			methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return methodInfo.env->NewGlobalRef(ouyaController);
		}
        return NULL;
    }
    
    bool isOuyaButtonPressed(OuyaButton button, jobject ouyaControllerGlobalRef)
    {
        JniMethodInfo methodInfo;
        
        bool isMethodAvailable = JniHelper::getMethodInfo(methodInfo,
                                                          "tv/ouya/console/api/OuyaController",
                                                          "getButton",
                                                          "(I)Z");
        
        if (isMethodAvailable)
        {
            bool buttonPressed = methodInfo.env->CallBooleanMethod(ouyaControllerGlobalRef,
                                                                  methodInfo.methodID,
                                                                  button);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return buttonPressed;
        }
        return false;
    }
    
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyDown(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId)
    {
        CCLOG("Received KeyDownEvent %d from Device: %d",keyCode,deviceId);
    }
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyUp(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId)
    {
        CCLOG("Received KeyUpEvent %d from Device: %d",keyCode,deviceId);
    }
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeGenericMotionEvent(JNIEnv* env, jobject thiz, jint deviceId)
    {
        ;
    }
    
    bool deleteGlobalJNIRef(jobject globalRef)
    {
        JNIEnv *env;
        if (JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
            return false;
        else
        {
            env->DeleteGlobalRef(globalRef);
            return true;
        }
    }
}