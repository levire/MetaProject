/****************************************************************************
 Created by Levire UG (haftungsbeschraenkt) & Co. KG , http://www.levire.com
 
 This program is free software. It comes without any warranty, to
 the extent permitted by applicable law. You can redistribute it
 and/or modify it under the terms of the Do What The Fuck You Want
 To Public License, Version 2, as published by Sam Hocevar. See
 http://www.wtfpl.net/ for more details.
 
 ****************************************************************************/

#include "TestRunnerScene.h"
#include "AppMacros.h"
#include "CocosUnitTestResultPrinter.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    
    this->testIt();
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
    testing::InitGoogleMock(&argc, const_cast<char**>(&argv));
    
    // Gets hold of the event listener list.
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    
    // Delete default printer
    delete listeners.Release(listeners.default_result_printer());
    
    // Adds a listener to the end.  Google Test takes the ownership.
    listeners.Append(new testing::CocosUnitTestResultPrinter());
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
