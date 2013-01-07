/****************************************************************************
 Created by Levire UG (haftungsbeschraenkt) & Co. KG , http://www.levire.com
 
 This program is free software. It comes without any warranty, to
 the extent permitted by applicable law. You can redistribute it
 and/or modify it under the terms of the Do What The Fuck You Want
 To Public License, Version 2, as published by Sam Hocevar. See
 http://www.wtfpl.net/ for more details.
 
 ****************************************************************************/

#ifndef __CC_OUYA_CONTROLLER_H__
#define __CC_OUYA_CONTROLLER_H__

#include <map>
#include <vector>
#include <jni.h>
#include "platform/ouya/jni/Java_com_levire_ouyabind_Controller.h"
#include "cocos2d.h"

NS_CC_BEGIN

class CC_DLL CCOuyaController;
class IOuyaControllerListener
{
public:
	virtual void onControllerKeyDown(int keyCode, CCOuyaController* controller) =0;
	virtual void onControllerKeyUp(int keyCode, CCOuyaController* controller) =0;
    
    virtual void onControllerLeftStickMotion(float axisXValue, float axisYValue, CCOuyaController* controller) =0;
    virtual void onControllerRightStickMotion(float axisXValue, float axisYValue, CCOuyaController* controller) =0;
};

class CC_DLL CCOuyaController
{
public:

	static CCOuyaController* controllerByDeviceId(int deviceId);
	static void onKeyDown(int keyCode, int deviceId);
	static void onKeyUp(int keyCode, int deviceId);
    
    static void onLeftStickMotion(float axisXValue, float axisYValue, int deviceId);
    static void onRightStickMotion(float axisXValue, float axisYValue, int deviceId);

	static void addListener(IOuyaControllerListener* listener);
	static void removeListener(IOuyaControllerListener* listener);
	static bool registered(IOuyaControllerListener* listener);

	static void freeControllerCache();

	bool isButtonPressed(OuyaControllerButton button);

	virtual ~CCOuyaController();

private:

	CCOuyaController(jobject jniLinkToOuyaController, int deviceId);

	static CCOuyaController* cachedControllerByDeviceId(int deviceId);
	static void cacheController(CCOuyaController* controller);

	int deviceId;
	jobject jniLinkToOuyaController;

	typedef std::map<int, CCOuyaController*> Controllers;
	static Controllers controllers;

	typedef std::vector<IOuyaControllerListener*> Listeners;
	static Listeners listeners;	
};

NS_CC_END //__CC_OUYA_CONTROLLER_H__

#endif
