// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAST may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#include "testCase.h"
#include "castCmd.h"
#include "cmdLine.h"

#include "trace.h"

#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include <sys/stat.h>
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
    CK(false);
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

    CK(success);
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
	
    CK(success);
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
	
    CK(success);
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

    CK(false == cmdExecuted);
}
END_DEF

DEFINE_TEST(ExecuteCreateAddTestCmdTest)
void setUp()
{
  mkdir("testTmp", 0775);
  chdir("testTmp");
}

void tearDown()
{
  remove("myTest.mak");
  remove("myTest.tpp");
  remove("Makefile");

  chdir("..");
  
  if(0 != rmdir("testTmp"))
    cas_print("Can't rmdir(): " << strerror(errno));
}

void testCmdExecutes(const cas::CmdLine& cmdLine)
{
    bool cmdExecuted(cas::CastCmd::executeCmd(cmdLine));

    CK(cmdExecuted);
}

void verifyTargetMakefileExists(const cas::CmdLine& cmdLine)
{
    std::string mkFile(cmdLine.args.back());
    mkFile += ".mak";

    CK(fileExists(mkFile));
}

void verifyTargetInMakefile(const cas::CmdLine& cmdLine)
{
    std::string mkFile(cmdLine.args.back());
    mkFile += ".mak";
    std::string target("TGT := ");
    target += cmdLine.args.back();
    target += ".test";

    CK(verifyTarget(mkFile, target));
}

void verifyMainMakefileExists()
{
    CK(fileExists("Makefile"));
}

void verifyMainMakefileInternals(const cas::CmdLine& cmdLine)
{
    std::string mkFileName(cmdLine.args.back());
    mkFileName += ".mak";

    bool foundMkLine(false);
    bool foundGlobalTarget(false);
    bool foundAllTarget(false);

    std::string expectedMakeLine("$(MAKE) -f ");
    expectedMakeLine += mkFileName;
    expectedMakeLine += " $@";

    std::ifstream mkFile("Makefile");
    std::string buffer;
    
    while(std::getline(mkFile, buffer))
    {
        if(std::string::npos != buffer.find(expectedMakeLine))
	    foundMkLine = true;

        if(std::string::npos != buffer.find("%:"))
            foundGlobalTarget = true;
    }

    CK(foundMkLine);
    CK(foundGlobalTarget);
}

void verifyNoDuplicateMakeLines(const cas::CmdLine& cmdLine)
{
    std::string mkFileLine("\t$(MAKE) -f ");
    mkFileLine += cmdLine.args.back();
    mkFileLine += ".mak";
    mkFileLine += " $@";
    
    testCmdExecutes(cmdLine);
    testCmdExecutes(cmdLine);

    size_t count(0);
    std::ifstream mkfile("Makefile");
    std::string buffer;

    while(std::getline(mkfile, buffer))
    {
        if(std::string::npos != buffer.find(mkFileLine))
	    ++count;
    }
    
    CK(1 == count);
}

void run()
{
    cas::CmdLine cmdLine(0, 0);

    cmdLine.args.push_back("-addTestSuite");
    cmdLine.args.push_back("myTest");

    testCmdExecutes(cmdLine);
    verifyTargetMakefileExists(cmdLine);
    verifyTargetInMakefile(cmdLine);
    verifyMainMakefileExists();
    verifyMainMakefileInternals(cmdLine);
    verifyNoDuplicateMakeLines(cmdLine);
}
END_DEF
