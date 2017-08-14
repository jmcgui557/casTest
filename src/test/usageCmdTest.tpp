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

#include "castCmd.h"
#include "cmdLine.h"

#include "castUtil.h" //mock

#include <string>
#include <sstream>

//code under test
#include "../usageCmd.cpp"
#include "../usage.cpp"

DEFINE_BASE(UsageBase)
int argc;
const char* argv[3];
cas::CmdLine* cmdLine;

void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-invalidCmd";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void tearDown()
{
    delete cmdLine;
}
END_DEF

DEFINE_TEST_FROM(UsageCmdPrintsUsageStatement, UsageBase)
void run()
{
    std::string expected("casTest: UNRECOGNIZED command: -usage\n"
                         "\nUSAGE:"
                         "\n\tcasTest -addTestSuite <testSuiteName>"
                         "\n\tcasTest <testLib1> [<testLib2> <...testLibN>]"
                         "\n"
                         "\n\tcasTest -about"
                         "\n\tcasTest -help"
                         "\n\tcasTest -version\n");

    std::ostringstream out;
    cas::UsageCmd usage(*cmdLine, out);

    usage.exec();

    CK(expected == out.str());
}
END_DEF

DEFINE_TEST(UsageCmdPrintsHelpMsgWhenInvokedWithHelpOption)
int argc;
const char* argv[3];
cas::CmdLine* cmdLine;

void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-help";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void tearDown()
{
    delete cmdLine;
}

void run()
{
    std::string expected("\nUSAGE:"
                         "\n\tcasTest -addTestSuite <testSuiteName>"
                         "\n\tcasTest <testLib1> [<testLib2> <...testLibN>]"
                         "\n"
                         "\n\tcasTest -about"
                         "\n\tcasTest -help"
                         "\n\tcasTest -version\n");

    std::ostringstream out;
    cas::UsageCmd usage(*cmdLine, out);

    usage.exec();

    CK(expected == out.str());
}

END_DEF


