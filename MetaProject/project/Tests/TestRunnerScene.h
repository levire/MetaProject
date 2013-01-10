#ifndef __TEST_RUNNER_SCENE_H__
#define __TEST_RUNNER_SCENE_H__

#include "cocos2d.h"

class TestRunner : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestRunner);
    
private:
    void testIt();
    void initTestingFramework();
    void runTests();
    void killApp();
};

#endif // __TEST_RUNNER_SCENE_H__
