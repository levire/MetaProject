/****************************************************************************
 Created by Levire UG (haftungsbeschraenkt) & Co. KG , http://www.levire.com
 
 This program is free software. It comes without any warranty, to
 the extent permitted by applicable law. You can redistribute it
 and/or modify it under the terms of the Do What The Fuck You Want
 To Public License, Version 2, as published by Sam Hocevar. See
 http://www.wtfpl.net/ for more details.
 
 ****************************************************************************/

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

CCOuyaController::~CCOuyaController() 
{
	deleteOuyaControllerJNIRef(jniLinkToOuyaController);
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

int CCOuyaController::getDeviceId()
{
	return getOuyaControllerDeviceId(this->jniLinkToOuyaController);
}

int CCOuyaController::getPlayerNum()
{
	return getOuyaControllerPlayerNum(this->jniLinkToOuyaController);
}

bool CCOuyaController::isButtonPressed(OuyaControllerButton button)
{
	return isOuyaButtonPressed(button, this->jniLinkToOuyaController);
}

float CCOuyaController::getAxisValue(OuyaControllerAxis axis)
{
	return getOuyaAxisValue(axis, this->jniLinkToOuyaController);
}

void CCOuyaController::freeControllerCache()
{
	for (Listeners::iterator it = CCOuyaController::listeners.begin();
		it != CCOuyaController::listeners.end();
		it++)
	{
		delete (*it);
	}
	CCOuyaController::listeners.clear();
}

NS_CC_END