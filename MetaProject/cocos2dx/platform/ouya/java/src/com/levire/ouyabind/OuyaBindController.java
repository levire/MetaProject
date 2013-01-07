package com.levire.ouyabind;

import tv.ouya.console.api.OuyaController;
import android.util.Log;
import android.view.KeyEvent;

public class OuyaBindController
{	
	public static OuyaController getControllerByPlayer(int playerNum) {
		Log.d("OUYA Controller", "getControllerByPlayer with Player: "+playerNum);
		OuyaController ouyaController = OuyaController.getControllerByPlayer(playerNum);
		Log.d("OUYA Controller", "Found Controller: "+ouyaController);
		return ouyaController;
	}
	
	public static OuyaController getControllerByDeviceId(int deviceId)
	{
		OuyaController controller = OuyaController.getControllerByDeviceId(deviceId);
		Log.d("OUYA Controller", "Got controller: "+controller);
		return controller;
	}
	
	public static native void onNativeKeyDown(final int pKeyCode, final int deviceId);
	public static boolean onKeyDown(final int pKeyCode, final KeyEvent pKeyEvent)
	{
		OuyaBindController.onNativeKeyDown(pKeyCode, pKeyEvent.getDeviceId());
		return OuyaController.onKeyDown(pKeyCode, pKeyEvent);
	}
	
	public static native void onNativeKeyUp(final int pKeyCode, final int deviceId);
	public static boolean onKeyUp(final int pKeyCode, final KeyEvent pKeyEvent)
	{
		OuyaBindController.onNativeKeyUp(pKeyCode, pKeyEvent.getDeviceId());
		return OuyaController.onKeyUp(pKeyCode, pKeyEvent);
	}
	
	public static native void onNativeGenericMotionEvent(final int deviceId);
	public static boolean onGenericMotionEvent(android.view.MotionEvent event)
	{
		OuyaBindController.onNativeGenericMotionEvent(event.getDeviceId());
		return OuyaController.onGenericMotionEvent(event);
	}
}
