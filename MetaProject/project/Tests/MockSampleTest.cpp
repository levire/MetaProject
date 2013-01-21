//
//  MockSampleTest.cpp
//  LevireTemplate
//
//  Created by Daniel Kiedrowski on 17.01.13.
//
//  Provides a basic example of a unit test 
//  using gtest and gmock

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SampleToMock.h"

// Create a mock using gmock
class SampleMock : public SampleToMock
{
public:
	MOCK_METHOD2(add, int(int a, int b));
};

// To use a test fixture, derive a class from testing::Test.
class MockSampleFixture : public testing::Test {
 protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.

  virtual void SetUp() 
  {
    unmockedClass = new SampleToMock();
    mockedClass = new SampleMock();
  }

  virtual void TearDown() 
  {
  	delete unmockedClass;
  	unmockedClass = (SampleToMock *)0;

	delete mockedClass;
  	mockedClass = (SampleMock *)0;  	
  }

  SampleToMock *unmockedClass;
  SampleMock *mockedClass;
};


TEST_F(MockSampleFixture, TestUnmockedClass) 
{
	// This tests the original class object, 
	// not the mocked one.
	EXPECT_EQ(3, unmockedClass->add(1,2));
}

using ::testing::Return;
TEST_F(MockSampleFixture, TestMockedClass) 
{
	// Expected to be called once.
	EXPECT_CALL(*mockedClass, add(1,2))
      .Times(1)
      .WillRepeatedly(Return(3));
	
	// Call once!
	EXPECT_EQ(3, mockedClass->add(1,2));
}