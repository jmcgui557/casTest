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
bool run()
{
    return true;
}
END_DEF

DEFINE_BASE(FailureTestCase)
bool run()
{
    return false;
}
END_DEF

DEFINE_BASE(UnknownExceptionTestCase)
bool run()
{
   throw 0;
	
    return false;
}
END_DEF

DEFINE_BASE(StdExceptionTestCase)
bool run()
{
    bool success(false);
	
    if(!success)
    {
        throw std::range_error("Test exception");
    }
	
    return false;
}
END_DEF

DEFINE_BASE(TestCaseErrorTestCase)
void setUp()
{}
    
bool run()
{
    throw TestCase::Error("TestCase::Error");
	
    return false;
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

bool run()
{
    return test_->run();
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
    
bool run()
{
    return TestCaseTest::run();
}
END_DEF

DEFINE_TEST_FROM(FailureTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new FailureTestCase());
}

bool run()
{
    return false == TestCaseTest::run();
}
END_DEF
    
DEFINE_TEST_FROM(TestCaseErrorTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new TestCaseErrorTestCase);
}

bool run()
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
	
    return success;
}
END_DEF

DEFINE_TEST_FROM(StdExceptionTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new StdExceptionTestCase);
}

bool run()
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
	
    return success;
}
END_DEF

DEFINE_TEST_FROM(UnknownExceptionTestCaseTest, TestCaseTest)
void setUp()
{
    setTest(new UnknownExceptionTestCase);
}
    
bool run()
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
	
    return success;
}
END_DEF


//------------------------------------------

extern "C"
{
    void createTests(std::vector<cas::TestCase*>& tests)
    {
        tests.push_back(new SuccessTestCaseTest);
        tests.push_back(new FailureTestCaseTest);
        tests.push_back(new TestCaseErrorTestCaseTest);
        tests.push_back(new StdExceptionTestCaseTest);
        tests.push_back(new UnknownExceptionTestCaseTest);
    }
}


