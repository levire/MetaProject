#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "platform/ouya/CCOuyaController.h"
#include <jni.h>

class HelloWorld : public cocos2d::CCLayer, public cocos2d::IOuyaControllerListener
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

    virtual void onControllerKeyDown(int keyCode, cocos2d::CCOuyaController* controller);
	virtual void onControllerKeyUp(int keyCode, cocos2d::CCOuyaController* controller);
};

#endif // __HELLOWORLD_SCENE_H__
