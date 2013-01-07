#include "CCOuyaController.h"
#include "jni/Java_com_levire_ouyabind_Controller.h"

NS_CC_BEGIN

CCOuyaController::Controllers CCOuyaController::controllers;

CCOuyaController* CCOuyaController::controllerByDeviceId(int deviceId)
{
	CCOuyaController* cachedOuyaController = CCOuyaController::cachedControllerByDeviceId(deviceId);
	if (cachedOuyaController != NULL) 
	{
		return cachedOuyaController;
	}

	jobject jniLinkToOuyaController = getOuyaControllerByDeviceId(deviceId);
	if (jniLinkToOuyaController != NULL)
	{
		CCOuyaController* newOuyaController = new CCOuyaController(jniLinkToOuyaController, deviceId);
		CCOuyaController::cacheController(newOuyaController);
		return newOuyaController;
	}

	return NULL;
}

CCOuyaController* CCOuyaController::cachedControllerByDeviceId(int deviceId)
{
	return CCOuyaController::controllers[deviceId];
}

void CCOuyaController::cacheController(CCOuyaController* controller)
{
	CCOuyaController::controllers[controller->deviceId] = controller;
}

CCOuyaController::CCOuyaController(jobject jniLinkToOuyaController, int deviceId)
: jniLinkToOuyaController(jniLinkToOuyaController)
, deviceId(deviceId)
{

}

NS_CC_END