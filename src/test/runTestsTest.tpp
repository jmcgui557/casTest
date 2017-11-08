// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAST poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
//
// Copyright (c) 2017 Randall Lee White

#include "testCase.h"

#include "testLib.h" //mock

#include <stdexcept>
#include <sstream>

//code under test
#include "../runTests.cpp"

DEFINE_BASE(SuccessfulTest)
void run()
{
    CK(true);
}
END_DEF

DEFINE_BASE(ErrorTest)
void run()
{
    CK(false);
}
END_DEF

DEFINE_BASE(StdExceptTest)
void run()
{
    throw std::runtime_error("Runtime error");
}
END_DEF

DEFINE_BASE(UnknownExceptTest)
void run()
{
    throw 2;
}
END_DEF

SKIP_TEST(SkipTest)
void run()
{
    CK(true);
}
END_DEF
    
DEFINE_TEST(RunTestReportsSuccessOnSuccessfulTest)
void run()
{
    cas::TestSummary sum;
    std::string expected("ok 1 - SuccessfulTest\n");
    std::ostringstream out;
    SuccessfulTest test;

    cas::runTest(&test, 1, sum, out);

    CK(expected == out.str());
}
END_DEF

DEFINE_TEST(RunTestReportsFailureOnTestError)
void run()
{
    cas::TestSummary sum;
    std::string expected("not ok 1 - ErrorTest\n"
                         "\t---\n"
                         "\tCaught cas::Test::Error: Assertion(false) FAILED: runTestsTest.cpp:31\n"
                         "\t---\n");
    
    std::ostringstream out;
    ErrorTest test;

    cas::runTest(&test, 1, sum, out);

    CK(expected == out.str());
}

END_DEF

DEFINE_TEST(RunTestReportsFailueOnStdException)
void run()
{
    cas::TestSummary sum;
    std::string expected("not ok 1 - StdExceptTest\n"
                         "\t---\n"
                         "\tCaught std::exception: Runtime error\n"
                         "\t---\n");
    
    std::ostringstream out;
    StdExceptTest test;

    cas::runTest(&test, 1, sum, out);

    CK(expected == out.str());
}

END_DEF

DEFINE_TEST(RunTestReportsFailureOnUnknownException)
void run()
{
    cas::TestSummary sum;
    std::string expected("not ok 1 - UnknownExceptTest\n"
                         "\t---\n"
                         "\tCaught UNKNOWN EXCEPTION\n"
                         "\t---\n");
    
    std::ostringstream out;
    UnknownExceptTest test;

    cas::runTest(&test, 1, sum, out);

    CK(expected == out.str());
}

END_DEF

DEFINE_TEST(RunTestReportsTestSkippedOnSkippedTest)
void run()
{
    cas::TestSummary sum;
    std::string expected("skipped 1 - SkipTest\n");
    std::ostringstream out;
    SkipTest test;

    cas::runTest(&test, 1, sum, out);

    CK(expected == out.str());
}

END_DEF

DEFINE_TEST(RunTestsPrintsTestPlan)

std::vector<TestCase*> tests;

std::string getFirstLine(const std::string& s)
{
    std::string::size_type p(s.find('\n'));

    return std::string(s.begin(),
                       s.begin() + p);
}

void setUp()
{
    tests.push_back(new SuccessfulTest());
    tests.push_back(new ErrorTest());
    tests.push_back(new StdExceptTest());
    tests.push_back(new UnknownExceptTest());
}

void tearDown()
{
    destroyTests(tests);
}

void run()
{
    cas::TestSummary sum;

    std::string expected("1..4");
    std::ostringstream out;

    cas::runTests(tests, sum, out);

    CK(expected == getFirstLine(out.str()));
}

END_DEF

DEFINE_TEST(RunTestsFromLibraryThrowsStdRuntimeErrorIfNoTestsAreFound)
void run()
{
    cas::TestSummary sum;
    std::ostringstream out;

    EXPECT_THROW(cas::runTestsFromLibrary("myLib", sum, out), std::runtime_error);
}

END_DEF

DEFINE_TEST(RunTestsFromLibraryReportsLibraryBeingUsed)
void run()
{
    cas::TestSummary sum;
    std::ostringstream out;

    std::string expected("\ncasTest: Running tests from: myLib\n");

    try
    {
        cas::runTestsFromLibrary("myLib",
                                 sum,
                                 out);
    }
    catch(...)
    {}

    CK(expected == out.str());
}

END_DEF

DEFINE_TEST(RunTestsRunsTheTestsInTheLibrary)

void setUp()
{
    cas::TestLib::mockTests.push_back(new SuccessfulTest());
    cas::TestLib::mockTests.push_back(new SuccessfulTest());
}

void tearDown()
{
    destroyTests(cas::TestLib::mockTests);
    cas::TestLib::mockTests.clear();
}

void run()
{
    cas::TestSummary sum;
    std::ostringstream out;

    cas::runTestsFromLibrary("myLib",
                             sum,
                             out);

    CK(2 == sum.total());
}

END_DEF
