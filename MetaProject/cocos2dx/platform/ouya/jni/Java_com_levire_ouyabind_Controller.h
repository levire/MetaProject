#ifndef __Ouyabind_Controller_
#define __Ouyabind_Controller_

#include <jni.h>

extern "C"
{
    enum OuyaButton
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
        BUTTON_L3 = 106
    } ;
    
    
	jobject getOuyaControllerByPlayer(int playerNum);
    
    jobject getOuyaControllerByDeviceId(int deviceID);
    
    bool isOuyaButtonPressed(OuyaButton button, jobject ouyaControllerGlobalRef);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyDown(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyUp(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeGenericMotionEvent(JNIEnv* env, jobject thiz, jint deviceId);
    
    bool deleteOuyaControllerJNIRef(jobject globalRef);
}

#endif