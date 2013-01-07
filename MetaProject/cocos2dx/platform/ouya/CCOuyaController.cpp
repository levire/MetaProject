#include "CCOuyaController.h"
#include "jni/Java_com_levire_ouyabind_Controller.h"

NS_CC_BEGIN

CCOuyaController::Controllers CCOuyaController::controllers;
CCOuyaController::Listeners CCOuyaController::listeners;

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
		CCLOG("Created a new CCOuyaController for DeviceID %d", deviceId);
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

void CCOuyaController::onKeyDown(int keyCode, int deviceId)
{
	for (Listeners::iterator it = CCOuyaController::listeners.begin();
		it != CCOuyaController::listeners.end();
		it++)
	{
		(*it)->onControllerKeyDown(keyCode, CCOuyaController::controllerByDeviceId(deviceId));
	}
}

void CCOuyaController::onKeyUp(int keyCode, int deviceId)
{
	for (Listeners::iterator it = CCOuyaController::listeners.begin();
		it != CCOuyaController::listeners.end();
		it++)
	{
		(*it)->onControllerKeyUp(keyCode, CCOuyaController::controllerByDeviceId(deviceId));
	}
}

void CCOuyaController::onLeftStickMotion(float axisXValue, float axisYValue, int deviceId)
{
    for (Listeners::iterator it = CCOuyaController::listeners.begin();
         it != CCOuyaController::listeners.end();
         it++)
	{
		(*it)->onControllerLeftStickMotion(axisXValue, axisYValue, CCOuyaController::controllerByDeviceId(deviceId));
	}
}

void CCOuyaController::onRightStickMotion(float axisXValue, float axisYValue, int deviceId)
{
    for (Listeners::iterator it = CCOuyaController::listeners.begin();
         it != CCOuyaController::listeners.end();
         it++)
	{
		(*it)->onControllerRightStickMotion(axisXValue, axisYValue, CCOuyaController::controllerByDeviceId(deviceId));
	}
}

void CCOuyaController::addListener(IOuyaControllerListener* listener)
{
	if (!CCOuyaController::registered(listener))
		CCOuyaController::listeners.push_back(listener);
}

void CCOuyaController::removeListener(IOuyaControllerListener* listener)
{
	bool found = false;
	Listeners::iterator it = CCOuyaController::listeners.begin();
	while (!found && it != CCOuyaController::listeners.end())
	{
		found = (*it) == listener;
		if (!found)
			++it;
	}

	CCOuyaController::listeners.erase(it);
}

bool CCOuyaController::registered(IOuyaControllerListener* listener)
{
	for (Listeners::iterator it = CCOuyaController::listeners.begin();
		it != CCOuyaController::listeners.end();
		it++)
	{
		if ((*it) == listener)
			return true;
	}

	return false;
}

NS_CC_END