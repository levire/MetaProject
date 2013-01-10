#include "TestRunnerScene.h"
#include "AppMacros.h"

#include <gtest/gtest.h>

USING_NS_CC;

#define COCOS_DEBUG 1

CCScene* TestRunner::scene()
{
    CCScene *scene = CCScene::create();
    TestRunner *layer = TestRunner::create();
    scene->addChild(layer);
    return scene;
}

bool TestRunner::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->scheduleUpdate();
    return true;
}

void TestRunner::testIt()
{
    this->initTestingFramework();
    this->runTests();
    this->killApp();
}

void TestRunner::initTestingFramework()
{
    int argc = 1;
    const char* argv = "TestRunner";
    testing::InitGoogleTest(&argc, const_cast<char**>(&argv));
}

void TestRunner::runTests()
{
    int notPassed = RUN_ALL_TESTS();
    if (notPassed == true)
    {
        CCLOG("==== TESTS FAILED ====");
    }
    else
    {
        CCLOG("==== TESTS PASSED ====");
    }
    
}

void TestRunner::killApp()
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
