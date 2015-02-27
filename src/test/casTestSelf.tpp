// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAST may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2013-2015 Randall Lee White

#include "testCase.h"
#include "castCmd.h"
#include "cmdLine.h"

#include "trace.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

#include <sys/wait.h>
#include <unistd.h>

/*The following test cases (Derived from TestCase) used to represent all
  the possible test results when a test case is run.  TestCaseTest derived 
  classes below are then used to run and test the results of the 
  representative test cases.
*/
DEFINE_BASE(SuccessTestCase)
void run()
{}
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

//-----------------------------------------------------------------
bool fileExists(const std::string& filename)
{
  return -1 != access(filename.c_str(), F_OK);
}

bool verifyTarget(const std::string& makefileName,
                  const std::string& targetString)
{
    std::string grepCmd("grep ");
    grepCmd += '\"';
    grepCmd += targetString;
    grepCmd += '\"';
    grepCmd += ' ';
    grepCmd += makefileName;
    grepCmd += " > /dev/null";

    int err(system(grepCmd.c_str()));
    int stat(WEXITSTATUS(err));
   
    return 0 == stat;
}

//Command tests
DEFINE_TEST(NoCommandInCmdLineTest)
void run()
{
    cas::CmdLine cmdLine(0, 0);
    
    cmdLine.args.push_back("casTest");
    cmdLine.args.push_back("myTestLib");

    bool cmdExecuted(cas::CastCmd::executeCmd(cmdLine));

    Assert(false == cmdExecuted,
           "Should not create cmd from arg without leading \'-\'");
}
END_DEF

DEFINE_TEST(ExecuteCreateInitTestCmdDefaultMakefileTest)
void tearDown()
{
    remove("Makefile");
    remove("myTest.tpp");
}

void run()
{
    cas::CmdLine cmdLine(0, 0);

    cmdLine.args.push_back("-initTest");
    cmdLine.args.push_back("myTest");

    bool cmdExecuted(cas::CastCmd::executeCmd(cmdLine));

    Assert(cmdExecuted,
           "Failed to execute command");

    Assert(fileExists("Makefile"),
           "Makefile not found.");

    std::string target("TGT := ");
    target += cmdLine.args.back();

    Assert(verifyTarget("Makefile", target),
           "Couldn't find target line");

    std::string testSrc("TSTSRC := ");
    testSrc += cmdLine.args.back();
    testSrc += ".tpp";

    Assert(verifyTarget("Makefile", testSrc),
        "Couldn't find test source line");
	   
}
END_DEF

DEFINE_TEST(ExecuteCreateInitTestCmdCustomMakefileNameTest)
void tearDown()
{
    remove("myTest.mak");
    remove("myTest.tpp");
}

void run()
{
    cas::CmdLine cmdLine(0, 0);

    cmdLine.args.push_back("-initTest");
    cmdLine.args.push_back("myTest");
    cmdLine.args.push_back("myTest.mak");

    bool cmdExecuted(cas::CastCmd::executeCmd(cmdLine));

    std::string& mkFile(cmdLine.args.back());

    Assert(cmdExecuted,
           "Failed to execute command");

    Assert(fileExists(mkFile),
           "Makefile not found.");

    std::string target("TGT := ");
    target += cmdLine.args[1];

    Assert(verifyTarget(mkFile, target),
           "Couldn't find target line");

    std::string testSrc("TSTSRC := ");
    testSrc += cmdLine.args[1];
    testSrc += ".tpp";

    Assert(verifyTarget(mkFile, testSrc),
        "Couldn't find test source line");

}
END_DEF

