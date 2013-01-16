MetaProject
===========

MetaProject is a starting point for multi-target (including ouya) cocos2d-x projects. MetaProject consists of Cocos2D-x 2.0-x-2.0.4, the ODK (OUYA Development Kit) 0.0.5 and a custom JNI layer to bind the Ouya Controller.

The project/Classes/HelloWorldScene.cpp has a little example how to use the CCOuyaController class, when deploying for OUYA.

Levire encurages TDD. For this we added gtest 1.6 and Tests targets for iOS, Mac, Android and OUYA, which let you run the tests on the device. Tests has to be placed under project/Tests. A simple failing example is included.

We will expand this template according to our work and the development of the used frameworks.

Rights
------

All frameworks and the code are owned by their specific owners and distributed under their choosen license.

How to start
------------

1. Checkout this repository
2. Place your code under project/Classes and your unit tests under project/Tests
3. Enter your new files in the Android.mk in the Classes and Tests folder
4. Compile the code using the appropriate proj.* folder
5. Change the product and class names as you wish for the specific platforms

Contact us
----------

Website: http://www.levire.com
Blog: http://blog.levire.com
Mail: info@levire.com