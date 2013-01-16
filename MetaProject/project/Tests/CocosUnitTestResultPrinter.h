//
//  CocosUnitTestResultPrinter.h
//  LevireTemplate
//
//  Created by Daniel Kiedrowski on 16.01.13.
//  Based on the PrettyUnitTestResultPrinter of gtest 1.6
//

#ifndef __LevireTemplate__CocosUnitTestResultPrinter__
#define __LevireTemplate__CocosUnitTestResultPrinter__

#include <iostream>
#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"

namespace testing {

class CocosUnitTestResultPrinter : public TestEventListener {
public:
    CocosUnitTestResultPrinter() {}
    static void PrintTestName(const char * test_case, const char * test) {
        printf("%s.%s", test_case, test);
    }
    
    // The following methods override what's in the TestEventListener class.
    virtual void OnTestProgramStart(const UnitTest& /*unit_test*/) {}
    virtual void OnTestIterationStart(const UnitTest& unit_test, int iteration);
    virtual void OnEnvironmentsSetUpStart(const UnitTest& unit_test);
    virtual void OnEnvironmentsSetUpEnd(const UnitTest& /*unit_test*/) {}
    virtual void OnTestCaseStart(const TestCase& test_case);
    virtual void OnTestStart(const TestInfo& test_info);
    virtual void OnTestPartResult(const TestPartResult& result);
    virtual void OnTestEnd(const TestInfo& test_info);
    virtual void OnTestCaseEnd(const TestCase& test_case);
    virtual void OnEnvironmentsTearDownStart(const UnitTest& unit_test);
    virtual void OnEnvironmentsTearDownEnd(const UnitTest& /*unit_test*/) {}
    virtual void OnTestIterationEnd(const UnitTest& unit_test, int iteration);
    virtual void OnTestProgramEnd(const UnitTest& /*unit_test*/) {}
    
private:
    static void PrintFailedTests(const UnitTest& unit_test);
    
    internal::String test_case_name_;
};
    
}

#endif /* defined(__LevireTemplate__CocosUnitTestResultPrinter__) */
