#include "HelloWorldScene.h"
#include "AppMacros.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
#include "platform/ouya/jni/Java_com_levire_ouyabind_Controller.h"
#include "platform/ouya/CCOuyaController.h"
#include <jni.h>
#endif

USING_NS_CC;

#define COCOS_DEBUG 1

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
cocos2d::CCOuyaController* player[4];
#endif

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
    player[0] = NULL;
    player[1] = NULL;
    player[2] = NULL;
    player[3] = NULL;
    #endif
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    this->scheduleUpdate();
    
    CCLOG("Initialized scene");
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
    CCOuyaController::addListener(this);
    #endif
    return true;
}

void HelloWorld::update(float fDelta)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
    if (player[0] && player[0]->isButtonPressed(BUTTON_A))
    {
        CCLOG("Player 0 - Pressed A");
    }

    if (player[1] && player[1]->isButtonPressed(BUTTON_A))
    {
        CCLOG("Player 1 - Pressed A");
    }
    #endif
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_OUYA)
bool playerRegistered(cocos2d::CCOuyaController *controller)
{
    for (int i=0; i<4; i++) 
    {
        if (player[i] == controller)
            return true;
    }

    return false;
}

int registerPlayer(cocos2d::CCOuyaController *controller)
{
    if (playerRegistered(controller))
        return -1;

    for (int i=0; i<4; i++) 
    {
        if (player[i] == NULL)
        {
            player[i] = controller;
            return i;
        }
    }

    return -1;
}

int playerId(cocos2d::CCOuyaController *controller)
{
    for (int i=0; i<4; i++) 
    {
        if (player[i] == controller)
            return i;
    }

    return -1;
}

void HelloWorld::onControllerKeyDown(int keyCode, cocos2d::CCOuyaController* controller)
{
    if (!playerRegistered(controller))
    {
        int playerId = registerPlayer(controller);
        CCLOG("Player %d entered the game!", playerId);
    }
}

void HelloWorld::onControllerKeyUp(int keyCode, cocos2d::CCOuyaController* controller)
{
    //CCLOG("onControllerKeyUp(%d, %d)", keyCode, controller);
}

void HelloWorld::onControllerLeftStickMotion(float axisXValue, float axisYValue, cocos2d::CCOuyaController* controller)
{
    CCLOG("onControllerLEFTStick(%f, %f, %d)", axisXValue, axisYValue, controller);
}

void HelloWorld::onControllerRightStickMotion(float axisXValue, float axisYValue, cocos2d::CCOuyaController* controller)
{
    CCLOG("onControllerRIGHTStick(%f, %f, %d)", axisXValue, axisYValue, controller);
}
#endif
