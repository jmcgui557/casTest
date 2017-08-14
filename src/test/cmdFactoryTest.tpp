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

#include "castUtil.h" //mock

#include "aboutCmd.h"
#include "addTestSuiteCmd.h"
#include "castCmd.h"
#include "cmdLine.h"
#include "usageCmd.h"
#include "verCmd.h"
#include <sstream>

//code under test
#include "../cmdFactory.cpp"

DEFINE_BASE(FactoryTest)
int argc;
const char* argv[3];
cas::CmdLine* cmdLine;

void tearDown()
{
    delete cmdLine;
}

END_DEF

DEFINE_TEST_FROM(CmdFactoryCreatesAboutCmd, FactoryTest)
void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-about";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void run()
{
    cas::CastCmd* cmd(cas::CastCmdFactory::create(*cmdLine));

    CK(0 != cmd);
    CK("-about" == cmd->name());
}
END_DEF

DEFINE_TEST_FROM(CmdFactoryCreatesUsageCmdWhenInvalidCommandSpecified, FactoryTest)
void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-invalid";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void run()
{
    std::ostringstream out;
    cas::CastCmd* cmd(cas::CastCmdFactory::create(*cmdLine, out));

    CK(0 != cmd);

    cmd->exec();
    
    CK(std::string::npos != out.str().find("USAGE:"));
}

END_DEF

DEFINE_TEST_FROM(CmdFactoryCreatesUsageCmdWhenHelpCommandSpecified, FactoryTest)
void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-help";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void run()
{
    std::ostringstream out;
    cas::CastCmd* cmd(cas::CastCmdFactory::create(*cmdLine, out));

    CK(0 != cmd);

    cmd->exec();
    
    CK(std::string::npos != out.str().find("USAGE:"));
}

END_DEF

DEFINE_TEST_FROM(CmdFactoryCreatesAddTestSuiteCmdWhenSpecified, FactoryTest)
void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-addTestSuite";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void run()
{
    cas::CastCmd* cmd(cas::CastCmdFactory::create(*cmdLine));

    CK("-addTestSuite" == cmd->name());
}

END_DEF

DEFINE_TEST_FROM(CmdFactoryCreatesVerCmdWhenSpecified, FactoryTest)
void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-version";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void run()
{
    cas::CastCmd* cmd(cas::CastCmdFactory::create(*cmdLine));

    CK("-version" == cmd->name());
}

END_DEF

DEFINE_TEST_FROM(CmdFactoryReturnsNullIfFirstCharOfCmdIsNotMinusSign, FactoryTest)
void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "NotACommand";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void run()
{
    cas::CastCmd* cmd(cas::CastCmdFactory::create(*cmdLine));

    CK(0 == cmd);

}

END_DEF
