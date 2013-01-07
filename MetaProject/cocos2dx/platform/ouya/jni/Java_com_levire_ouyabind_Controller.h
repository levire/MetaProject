#ifndef __Ouyabind_Controller_
#define __Ouyabind_Controller_

#include <jni.h>

extern "C"
{
	jobject getOuyaControllerByPlayer(int playerNum);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyDown(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId);
    
    JNIEXPORT void JNICALL Java_com_levire_ouyabind_OuyaBindController_onNativeKeyUp(JNIEnv* env, jobject thiz, jint keyCode, jint deviceId);
}

#endif