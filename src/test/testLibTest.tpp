//The "Clean And Simple" (CAS) software framework, tools, and documentation
//are distributed under the terms of the MIT license a copy of which is
//included with this package (see the file "LICENSE" in the CAS poject tree's
//root directory).  CAST may be used for any purpose, including commercial
//purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
//"copyleft" restrictions, either.  Just download it and use it.
//
//Copyright (c) 2017 Randall Lee White

#include "testCase.h"

#include "dynLibUtil.h"

//code under test
#include "../testLib.cpp"

DEFINE_BASE(TestLibTest)
void* oldHandle;
cas::TestLib* testLib;

void setUp()
{
    testLib = new cas::TestLib("myTestLib");
}

void tearDown()
{
    delete testLib;
}

void run()
{
    bool success(false);
    
    try
    {
        cas::TestLib tlib("myTestLib");
    }
    catch(const cas::TestLib::Error& x)
    {
        success = true;
    }

    CK(success);
}
END_DEF

DEFINE_TEST_FROM(TestLibThrowsIfDlOpenReturnsNULL, TestLibTest)

void setUp()
{
    TestLibTest::setUp();
    
    oldHandle = cas::DynLibUtil::mock_dlhandleVal;
    cas::DynLibUtil::mock_dlhandleVal = 0;
}

void tearDown()
{
    cas::DynLibUtil::mock_dlhandleVal = oldHandle;
    TestLibTest::tearDown();
}
END_DEF

DEFINE_TEST_FROM(TestLibThrowsIfDlSymReturnsNULL, TestLibTest)
void* oldHandle;

void setUp()
{
    TestLibTest::setUp();
    
    oldHandle = cas::DynLibUtil::mock_dlsymVal;
    cas::DynLibUtil::mock_dlsymVal = 0;
}

void tearDown()
{
    cas::DynLibUtil::mock_dlsymVal = oldHandle;
    TestLibTest::tearDown();
}

END_DEF

DEFINE_TEST(ExerciseCreateAndDestroyTests)
void run()
{
    std::vector<cas::TestCase*> tests;
    cas::TestLib tlib("myTestLib");

    tlib.createTests(tests);
    tlib.destroyTests(tests);
}

END_DEF

