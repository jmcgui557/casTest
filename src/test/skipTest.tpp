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

struct SkipTest : cas::TestCase
{
    SkipTest()
        : cas::TestCase("SkipTest", true)
    {}
    
    void run()
    {

    }

private:
};

@SKIP
DEFINE_TEST(ThisTestsEnsuresThatWeSuccessfullyProcessSKIPTagDuringBuild)
//Will generate a build time error or will fail
//on failure..will generate a skipped test on success.
void run()
{
    CK(false);
}

END_DEF

DEFINE_TEST(SkippedTestThrowsTestSkipped)
void run()
{
    bool success(false);
    SkipTest skipTest;
    
    try
    {
        skipTest.run_();
    }
    catch(const TestCase::TestSkipped& x)
    {
        success = true;
    }

    CK(success);
}
END_DEF


