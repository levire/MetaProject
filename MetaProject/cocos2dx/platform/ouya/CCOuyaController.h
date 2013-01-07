#ifndef __CC_OUYA_CONTROLLER_H__
#define __CC_OUYA_CONTROLLER_H__

#include <map>
#include <jni.h>
#include "cocos2d.h"

NS_CC_BEGIN

class CC_DLL CCOuyaController
{
public:

	static CCOuyaController* controllerByDeviceId(int deviceId);

private:

	CCOuyaController(jobject jniLinkToOuyaController, int deviceId);

	static CCOuyaController* cachedControllerByDeviceId(int deviceId);
	static void cacheController(CCOuyaController* controller);

	int deviceId;
	jobject jniLinkToOuyaController;

	typedef std::map<int, CCOuyaController*> Controllers;
	static Controllers controllers;
};

NS_CC_END //__CC_OUYA_CONTROLLER_H__

#endif
