#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
#include "platform/ouya/CCOuyaController.h"
#include <jni.h>
#endif

class HelloWorld : public cocos2d::CCLayer
#if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
, public cocos2d::IOuyaControllerListener
#endif
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void update(float fDelta);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
    virtual void onControllerKeyDown(int keyCode, cocos2d::CCOuyaController* controller);
	virtual void onControllerKeyUp(int keyCode, cocos2d::CCOuyaController* controller);
    
    virtual void onControllerLeftStickMotion(float axisXValue, float axisYValue, cocos2d::CCOuyaController* controller);
    virtual void onControllerRightStickMotion(float axisXValue, float axisYValue, cocos2d::CCOuyaController* controller);
    #endif
};

#endif // __HELLOWORLD_SCENE_H__
