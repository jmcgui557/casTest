// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAS may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2013-2015 Randall Lee White

#include "testCase.h"

#include <vector>

/*The following test cases (Derived from TestCase) used to represent all
  the possible test results when a test case is run.  TestCaseTest derived 
  classes below are then used to run and test the results of the 
  representative test cases.
*/
DEFINE_BASE(SuccessTestCase)
void run()
{}
END_DEF

/*
  The Failure test case has become redundant in that it is
  identical to the TestCaseErrorTestCase.  This was a result
  of changing TestCase::run() from returning bool to returning
  void.
*/
DEFINE_BASE(FailureTestCase)
void run()
{
    throw xTest("Failure");
}
END_DEF

DEFINE_BASE(UnknownExceptionTestCase)
void run()
{
    throw 0;
}
END_DEF

DEFINE_BASE(StdExceptionTestCase)
void run()
{
    throw std::range_error("Test exception");
}
END_DEF

DEFINE_BASE(TestCaseErrorTestCase)
void setUp()
{}
    
void run()
{
    throw xTest("TestCase::Error");
}
END_DEF

DEFINE_BASE(TestCaseTest)
~TestCaseTest()
{
    delete test_;
}
void setUp()
{
    test_ = 0;
}

void run()
{
    test_->run();
}

protected:
void setTest(cas::TestCase* test)
{
    test_ = test;
}

private:
    cas::TestCase* test_;
END_DEF

DEFINE_TEST_FROM(SuccessTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new SuccessTestCase());
}
    
void run()
{
    TestCaseTest::run();
}
END_DEF

DEFINE_TEST_FROM(FailureTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new FailureTestCase());
}

void run()
{
    bool success(false);

    try
    {
        TestCaseTest::run();
    }
    catch(const TestCase::Error& x)
    {
        success = true;
    }

    if(!success)
        throw xTest("FailureTestCaseTest failed");
}
END_DEF
    
DEFINE_TEST_FROM(TestCaseErrorTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new TestCaseErrorTestCase);
}

void run()
{
    bool success(false);

    try
    {
        TestCaseTest::run();
    }
    catch(cas::TestCase::Error& x)
    {
        success = true;
    }
	
    if(!success)
        throw xTest("TestCaseErrorTestCaseTest failed");
}
END_DEF

DEFINE_TEST_FROM(StdExceptionTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new StdExceptionTestCase);
}

void run()
{
    bool success(false);
	
    try
    {
        TestCaseTest::run();
    }
    catch(std::exception& x)
    {
        success = true;
    }
	
    if(!success)
      throw xTest("StdExceptionTestCaseTest falied");
}
END_DEF

DEFINE_TEST_FROM(UnknownExceptionTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new UnknownExceptionTestCase);
}
    
void run()
{
    bool success(false);
	
    try
    {
        TestCaseTest::run();
    }
    catch(const cas::TestCase::Error& x)
    {}
    catch(const std::exception& x)
    {}
    catch(...)
    {
        success = true;
    }
	
    if(!success)
      throw xTest("UnknowExceptionTestCaseTest failed");
}
END_DEF
