#include "JniHelper.h"
#include <jni.h>
#include "Java_com_levire_ouyabind_Controller.h"

using namespace cocos2d;

extern "C"
{
	void getOuyaControllerByPlayer(int playerNum) 
	{
		JniMethodInfo methodInfo;
		bool isMethodAvailable = JniHelper::getStaticMethodInfo(
									methodInfo,
								   	"com/levire/ouyabind/OuyaBindController",
								   	"getControllerByPlayer",
								   	"()V");

		if (isMethodAvailable)
		{
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
												 methodInfo.methodID);
			methodInfo.env->DeleteLocalRef(methodInfo.classID);
		}
	}
}