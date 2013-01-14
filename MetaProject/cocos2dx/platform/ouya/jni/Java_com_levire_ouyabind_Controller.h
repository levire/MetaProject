/****************************************************************************
 Created by Levire UG (haftungsbeschraenkt) & Co. KG , http://www.levire.com
 
 This program is free software. It comes without any warranty, to
 the extent permitted by applicable law. You can redistribute it
 and/or modify it under the terms of the Do What The Fuck You Want
 To Public License, Version 2, as published by Sam Hocevar. See
 http://www.wtfpl.net/ for more details.
 
 ****************************************************************************/

#ifndef __Ouyabind_Controller_
#define __Ouyabind_Controller_

#include <jni.h>

extern "C"
{
    enum OuyaControllerButton
    {
        BUTTON_O = 96,
        BUTTON_U = 99,
        BUTTON_Y = 100,
        BUTTON_A = 97,
        BUTTON_L1 = 102,
        BUTTON_L2 = 104,
        BUTTON_R1 = 103,
        BUTTON_R2 = 105,
        BUTTON_SYSTEM = 3,
        BUTTON_DPAD_UP = 19,
        BUTTON_DPAD_DOWN = 20,
        BUTTON_DPAD_LEFT = 21,
        BUTTON_DPAD_RIGHT = 22,
        BUTTON_R3 = 107,
        BUTTON_L3 = 106,
        AXIS_L2 = 17,
        AXIS_R2 = 18
    };
    
    enum OuyaControllerAxis
    {
        AXIS_LS_X = 0,
        AXIS_LS_Y = 1,
        
        AXIS_RS_X = 11,
        AXIS_RS_Y = 14        
    };
    
    
	jobject getOuyaControllerByPlayer(int playerNum);
    
    jobject getOuyaControllerByDeviceId(int deviceID);
    
    bool isOuyaButtonPressed(OuyaControllerButton button, jobject ouyaControllerGlobalRef);
    
    float getOuyaAxisValue(OuyaControllerAxis controllerAxis, jobject ouyaControllerGlobalRef);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyDown(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyUp(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeLeftStickMotionEvent(JNIEnv* env, jobject thiz, jint deviceId, jfloat axisXValue, jfloat axisYValue);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeRightStickMotionEvent(JNIEnv* env, jobject thiz, jint deviceId, jfloat axisXValue, jfloat axisYValue);
    
    bool deleteOuyaControllerJNIRef(jobject globalRef);
}

#endif