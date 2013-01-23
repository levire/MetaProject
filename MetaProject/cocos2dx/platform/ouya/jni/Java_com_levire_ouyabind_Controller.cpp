/****************************************************************************
 Created by Levire UG (haftungsbeschraenkt) & Co. KG , http://www.levire.com
 
 This program is free software. It comes without any warranty, to
 the extent permitted by applicable law. You can redistribute it
 and/or modify it under the terms of the Do What The Fuck You Want
 To Public License, Version 2, as published by Sam Hocevar. See
 http://www.wtfpl.net/ for more details.
 
 ****************************************************************************/

#include "JniHelper.h"
#include <jni.h>
#include "Java_com_levire_ouyabind_Controller.h"
#include "platform/CCCommon.h"
#include "platform/ouya/CCOuyaController.h"

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
            return methodInfo.env->NewGlobalRef(ouyaController);
		}
        else
        {
            CCLOG("Error: Method 'tv.ouya.console.api.OuyaController.getControllerByPlayer' not available.");
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
        else
        {
            CCLOG("Error: Method 'tv.ouya.console.api.OuyaController.getControllerByDeviceId' not available.");
        }
        return NULL;
    }
    
    bool isOuyaButtonPressed(OuyaControllerButton button, jobject ouyaControllerJNI)
    {
        JniMethodInfo methodInfo;
        
        bool isMethodAvailable = JniHelper::getMethodInfo(methodInfo,
                                                          "tv/ouya/console/api/OuyaController",
                                                          "getButton",
                                                          "(I)Z");
        
        if (isMethodAvailable)
        {
            bool buttonPressed = methodInfo.env->CallBooleanMethod(ouyaControllerJNI,
                                                                  methodInfo.methodID,
                                                                  button);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return buttonPressed;
        }
        else
        {
            CCLOG("Error: Method 'tv.ouya.console.api.OuyaController.getButton' not available.");
        }
        return false;
    }
    
    float getOuyaAxisValue(OuyaControllerAxis controllerAxis, jobject ouyaControllerJNI)
    {
        JniMethodInfo methodInfo;
        
        bool isMethodAvailable = JniHelper::getMethodInfo(methodInfo,
                                                          "tv/ouya/console/api/OuyaController",
                                                          "getAxisValue",
                                                          "(I)F");
        
        if (isMethodAvailable)
        {
            float axisValue = methodInfo.env->CallFloatMethod(ouyaControllerJNI,
                                                              methodInfo.methodID,
                                                              controllerAxis);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return axisValue;
        }
        else
        {
            CCLOG("Error: Method 'tv.ouya.console.api.OuyaController.getAxisValue' not available.");
        }
        return 0.0f;
    }
    
    int getOuyaControllerDeviceId(jobject ouyaControllerJNI)
    {
        JniMethodInfo methodInfo;
        
        bool isMethodAvailable = JniHelper::getMethodInfo(methodInfo,
                                                          "tv/ouya/console/api/OuyaController",
                                                          "getDeviceId",
                                                          "()I");
        
        if (isMethodAvailable)
        {
            int deviceId = methodInfo.env->CallIntMethod(ouyaControllerJNI,
                                                         methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return deviceId;
        }
        else
        {
            CCLOG("Error: Method 'tv.ouya.console.api.OuyaController.getDeviceId' not available.");
        }
        return -1;
    }

    int getOuyaControllerPlayerNum(jobject ouyaControllerJNI)
    {
        JniMethodInfo methodInfo;
        
        bool isMethodAvailable = JniHelper::getMethodInfo(methodInfo,
                                                          "tv/ouya/console/api/OuyaController",
                                                          "getPlayerNum",
                                                          "()I");
        
        if (isMethodAvailable)
        {
            int playerNum = methodInfo.env->CallIntMethod(ouyaControllerJNI,
                                                          methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return playerNum;
        }
        else
        {
            CCLOG("Error: Method 'tv.ouya.console.api.OuyaController.getPlayerNum' not available.");
        }
        return -1;
    }
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyDown(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId)
    {
        CCOuyaController::onKeyDown(keyCode, deviceId);
    }
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyUp(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId)
    {
        CCOuyaController::onKeyUp(keyCode, deviceId);
    }
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeLeftStickMotionEvent(JNIEnv* env, jobject thiz, jint deviceId, jfloat axisXValue, jfloat axisYValue)
    {
        CCOuyaController::onLeftStickMotion(axisXValue, axisYValue,deviceId);
    }
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeRightStickMotionEvent(JNIEnv* env, jobject thiz, jint deviceId, jfloat axisXValue, jfloat axisYValue)
    {
        CCOuyaController::onRightStickMotion(axisXValue, axisYValue,deviceId);
    }
    
    bool deleteOuyaControllerJNIRef(jobject globalRef)
    {
        JNIEnv *env;
        if (JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
        {
            CCLOG("Error: Deleting global JReference failed.");
            return false;
        }
        else
        {
            env->DeleteGlobalRef(globalRef);
            return true;
        }
    }
}