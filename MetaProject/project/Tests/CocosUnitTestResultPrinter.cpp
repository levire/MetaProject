//
//  CocosUnitTestResultPrinter.cpp
//  LevireTemplate
//
//  Created by Daniel Kiedrowski on 16.01.13.
//  Based on the PrettyUnitTestResultPrinter of gtest 1.6
//

#include "CocosUnitTestResultPrinter.h"
#include "cocos2d.h"

namespace testing {
    
    static internal::String FormatCountableNoun(int count,
                                                const char * singular_form,
                                                const char * plural_form)
    {
        return internal::String::Format("%d %s", count,
                                        count == 1 ? singular_form : plural_form);
    }
    
    // Formats the count of tests.
    static internal::String FormatTestCount(int test_count)
    {
        return FormatCountableNoun(test_count, "test", "tests");
    }
    
    // Formats the count of test cases.
    static internal::String FormatTestCaseCount(int test_case_count) {
        return FormatCountableNoun(test_case_count, "test case", "test cases");
    }
    
    // Converts a TestPartResult::Type enum to human-friendly string
    // representation.  Both kNonFatalFailure and kFatalFailure are translated
    // to "Failure", as the user usually doesn't care about the difference
    // between the two when viewing the test result.
    static const char * TestPartResultTypeToString(TestPartResult::Type type)
    {
        switch (type)
        {
            case TestPartResult::kSuccess:
                return "Success";
                
            case TestPartResult::kNonFatalFailure:
            case TestPartResult::kFatalFailure:
                return "Failure\n";
            default:
                return "Unknown result type";
        }
    }
    
    static internal::String PrintTestPartResultToString(const TestPartResult& test_part_result) {
        return (Message()
                << internal::FormatFileLocation(test_part_result.file_name(),
                                                test_part_result.line_number())
                << " " << TestPartResultTypeToString(test_part_result.type())
                << test_part_result.message()).GetString();
    }
    
    // Prints a TestPartResult.
    static void PrintTestPartResult(const TestPartResult& test_part_result)
    {
        const internal::String& result =
        PrintTestPartResultToString(test_part_result);
        CCLOG("%s\n", result.c_str());
    }

    // Fired before each iteration of tests starts.
    void CocosUnitTestResultPrinter::OnTestIterationStart(const UnitTest& unit_test, int iteration)
    {
        if (GTEST_FLAG(repeat) != 1)
            CCLOG("\nRepeating all tests (iteration %d) . . .\n\n", iteration + 1);
        
        const char* const filter = GTEST_FLAG(filter).c_str();
        
        // Prints the filter if it's not *.  This reminds the user that some
        // tests may be skipped.
        if (!internal::String::CStringEquals(filter, "*")) {
            CCLOG("Note: %s filter = %s\n", GTEST_NAME_, filter);
        }
        
        if (GTEST_FLAG(shuffle)) {
            CCLOG("Note: Randomizing tests' orders with a seed of %d .\n",
                   unit_test.random_seed());
        }
        
        CCLOG("[==========] ");
        CCLOG("Running %s from %s.\n",
               FormatTestCount(unit_test.test_to_run_count()).c_str(),
               FormatTestCaseCount(unit_test.test_case_to_run_count()).c_str());
    }

    void CocosUnitTestResultPrinter::OnEnvironmentsSetUpStart(const UnitTest&)
    {
        CCLOG("[----------] ");
        CCLOG("Global test environment set-up.\n");
    }

    void CocosUnitTestResultPrinter::OnTestCaseStart(const TestCase& test_case)
    {
        test_case_name_ = test_case.name();
        const internal::String counts =
        FormatCountableNoun(test_case.test_to_run_count(), "test", "tests");
        CCLOG("[----------] ");
        CCLOG("%s from %s", counts.c_str(), test_case_name_.c_str());
        if (test_case.type_param() == NULL) {
            CCLOG("\n");
        } else {
            CCLOG(", where TypeParam = %s\n", test_case.type_param());
        }
    }

    void CocosUnitTestResultPrinter::OnTestStart(const TestInfo& test_info)
    {
        CCLOG("[ RUN      ] ");
        PrintTestName(test_case_name_.c_str(), test_info.name());
        CCLOG("\n");
    }
    
    void PrintFullTestCommentIfPresent(const TestInfo& test_info)
    {
        const char* const type_param = test_info.type_param();
        const char* const value_param = test_info.value_param();
        
        if (type_param != NULL || value_param != NULL)
        {
            CCLOG(", where ");
            if (type_param != NULL) {
                CCLOG("TypeParam = %s", type_param);
                if (value_param != NULL)
                    CCLOG(" and ");
            }
            if (value_param != NULL) {
                CCLOG("GetParam() = %s", value_param);
            }
        }
    }

    // Called after an assertion failure.
    void CocosUnitTestResultPrinter::OnTestPartResult(const TestPartResult& result)
    {
        // If the test part succeeded, we don't need to do anything.
        if (result.type() == TestPartResult::kSuccess)
        {
            return;
        }
        
        // Print failure message from the assertion (e.g. expected this and got that).
        PrintTestPartResult(result);
    }

    void CocosUnitTestResultPrinter::OnTestEnd(const TestInfo& test_info)
    {
        if (test_info.result()->Passed())
        {
            CCLOG("[       OK ] ");
        }
        else
        {
            CCLOG("[  FAILED  ] ");
        }
        
        PrintTestName(test_case_name_.c_str(), test_info.name());
        if (test_info.result()->Failed())
        {
            PrintFullTestCommentIfPresent(test_info);
        }
        
        if (GTEST_FLAG(print_time))
        {
            CCLOG(internal::StreamableToString(test_info.result()->elapsed_time()).c_str());
        }
        else
        {
            CCLOG("\n");
        }
    }

    void CocosUnitTestResultPrinter::OnTestCaseEnd(const TestCase& test_case)
    {
        if (!GTEST_FLAG(print_time)) return;
        
        test_case_name_ = test_case.name();
        const internal::String counts =
        FormatCountableNoun(test_case.test_to_run_count(), "test", "tests");
        CCLOG("[----------] ");
        CCLOG("%s from %s (%s ms total)\n\n",
               counts.c_str(), test_case_name_.c_str(),
               internal::StreamableToString(test_case.elapsed_time()).c_str());
    }
    
    void CocosUnitTestResultPrinter::OnEnvironmentsTearDownStart(const UnitTest&)
    {
        CCLOG("[----------] ");
        CCLOG("Global test environment tear-down\n");
    }

    // Internal helper for printing the list of failed tests.
    void CocosUnitTestResultPrinter::PrintFailedTests(const UnitTest& unit_test)
    {
        const int failed_test_count = unit_test.failed_test_count();
        if (failed_test_count == 0)
        {
            return;
        }
        
        for (int i = 0; i < unit_test.total_test_case_count(); ++i)
        {
            const TestCase& test_case = *unit_test.GetTestCase(i);
            if (!test_case.should_run() || (test_case.failed_test_count() == 0))
            {
                continue;
            }
            for (int j = 0; j < test_case.total_test_count(); ++j)
            {
                const TestInfo& test_info = *test_case.GetTestInfo(j);
                if (!test_info.should_run() || test_info.result()->Passed())
                {
                    continue;
                }
                CCLOG("[  FAILED  ] ");
                CCLOG("%s.%s", test_case.name(), test_info.name());
                PrintFullTestCommentIfPresent(test_info);
                CCLOG("\n");
            }
        }
    }

    void CocosUnitTestResultPrinter::OnTestIterationEnd(const UnitTest& unit_test, int /*iteration*/) {
        CCLOG("[==========] ");
        CCLOG("%s from %s ran.",
               FormatTestCount(unit_test.test_to_run_count()).c_str(),
               FormatTestCaseCount(unit_test.test_case_to_run_count()).c_str());
        if (GTEST_FLAG(print_time)) {
            CCLOG(" (%s ms total)",
                   internal::StreamableToString(unit_test.elapsed_time()).c_str());
        }
        CCLOG("\n");
        CCLOG("[  PASSED  ] ");
        CCLOG("%s.\n", FormatTestCount(unit_test.successful_test_count()).c_str());
        
        int num_failures = unit_test.failed_test_count();
        if (!unit_test.Passed()) {
            const int failed_test_count = unit_test.failed_test_count();
            CCLOG("[  FAILED  ] ");
            CCLOG("%s, listed below:\n", FormatTestCount(failed_test_count).c_str());
            PrintFailedTests(unit_test);
            CCLOG("\n%2d FAILED %s\n", num_failures,
                   num_failures == 1 ? "TEST" : "TESTS");
        }
        
        int num_disabled = unit_test.disabled_test_count();
        if (num_disabled && !GTEST_FLAG(also_run_disabled_tests)) {
            if (!num_failures) {
                CCLOG("\n");  // Add a spacer if no FAILURE banner is displayed.
            }
            CCLOG("  YOU HAVE %d DISABLED %s\n\n",
                          num_disabled,
                          num_disabled == 1 ? "TEST" : "TESTS");
        }
    }
    
}

