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
		boolean handled = OuyaController.onKeyDown(pKeyCode, pKeyEvent);
		OuyaBindController.onNativeKeyDown(pKeyCode, pKeyEvent.getDeviceId());
		return handled;
	}
	
	public static native void onNativeKeyUp(final int pKeyCode, final int deviceId);
	public static boolean onKeyUp(final int pKeyCode, final KeyEvent pKeyEvent)
	{
		boolean handled = OuyaController.onKeyUp(pKeyCode, pKeyEvent);
		OuyaBindController.onNativeKeyUp(pKeyCode, pKeyEvent.getDeviceId());
		return handled;
	}
	
	public static native void onNativeLeftStickMotionEvent(final int deviceId, final float axisXValue, final float axisYValue);
	public static native void onNativeRightStickMotionEvent(final int deviceId, final float axisXValue, final float axisYValue);
	
	public static boolean onGenericMotionEvent(android.view.MotionEvent event)
	{
		boolean handled = OuyaController.onGenericMotionEvent(event);
		OuyaController controller = OuyaController.getControllerByDeviceId(event.getDeviceId());
		
		OuyaBindController.onNativeLeftStickMotionEvent(event.getDeviceId(), controller.getAxisValue(OuyaController.AXIS_LS_X), controller.getAxisValue(OuyaController.AXIS_LS_Y));
		OuyaBindController.onNativeRightStickMotionEvent(event.getDeviceId(), controller.getAxisValue(OuyaController.AXIS_RS_X), controller.getAxisValue(OuyaController.AXIS_RS_Y));
		return handled;
	}
}
