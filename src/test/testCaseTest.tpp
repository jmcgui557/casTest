// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#include "testCase.h"
#include "trace.h"

#include <string>

//code under test
#include "../testCase.cpp"

DEFINE_BASE(FailureTestCase)
void run()
{
    CK(false);
}

END_DEF

SKIP_TEST(SkipTestCase)
void run()
{
    CK(true);
}
END_DEF

DEFINE_TEST(WhenConstructedToSkip_TestCaseThrowsTestCase_TestSkipped)
void run()
{
    bool success(false);
    SkipTestCase test;

    try
    {
        test.run_();
    }
    catch(const TestCase::TestSkipped& x)
    {
        success = true;
    }

    CK(success);
}

END_DEF

DEFINE_TEST(OnAssertFailureTestCaseThrowsTestCase_Error)
void run()
{
    bool success(false);
    FailureTestCase test;

    std::string expectedErrText("Assertion(false) FAILED: testCaseTest.cpp:22");

    try
    {
        test.run_();
    }
    catch(const TestCase::Error& x)
    {
        success = true;

        CK(0 == expectedErrText.compare(x.what()));
    }

    CK(success);
}
END_DEF

struct DeleteCounter : cas::TestCase
{
    DeleteCounter()
        : TestCase("DeleteCounter")
    {}

    ~DeleteCounter()
    {
        ++deletes;
    }

    void run()
    {

    }

    static size_t deletes;
};

size_t DeleteCounter::deletes(0);

DEFINE_TEST(ExerciseDeleteTests)
void setUp()
{
    DeleteCounter::deletes = 0;
}

void run()
{
    std::vector<cas::TestCase*> tests;

    for(size_t t(0); t < 10; ++t)
        tests.push_back(new DeleteCounter());

    destroyTests(tests);

    cas_print("deletes: " << DeleteCounter::deletes);
    CK(10 == DeleteCounter::deletes);
}

END_DEF
