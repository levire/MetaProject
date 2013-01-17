//
//  MockSampleTest.cpp
//  LevireTemplate
//
//  Created by Daniel Kiedrowski on 17.01.13.
//
//  Provides a basic example of a unit test 
//  using gtest and gmock

#include <gtest/gtest.h>
#include "SampleToMock.h"

// To use a test fixture, derive a class from testing::Test.
class MockSampleFixture : public testing::Test {
 protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.

  virtual void SetUp() 
  {
    unmockedClass = new SampleToMock();
  }

  virtual void TearDown() 
  {
  	delete unmockedClass;
  	unmockedClass = (SampleToMock *)0;
  }

  SampleToMock *unmockedClass;
};


TEST_F(MockSampleFixture, TestUnmockedClass) 
{
	// This tests the original class object, 
	// not the mocked one.
	EXPECT_EQ(3, unmockedClass->add(1,2));
}