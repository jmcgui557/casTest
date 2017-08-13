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

#include "cmdLine.h"

DEFINE_BASE(CmdLineTest)
int argc;
const char* argv[5];

END_DEF

DEFINE_TEST_FROM(CmdLineArgsIsEmptyIfArgcIsOne, CmdLineTest)
void setUp()
{
    argc = 1;
    argv[0] = "casTest";
    argv[1] = 0;
    argv[2] = 0;
    argv[3] = 0;
    argv[4] = 0;
}

void run()
{
    cas::CmdLine cmdLine(argc, argv);

    CK(0 == cmdLine.args.size());
}
END_DEF

DEFINE_TEST_FROM(ArgsReflectCommandLineMinusExecName, CmdLineTest)
void setUp()
{
    argc = 3;
    argv[0] = "casTest";
    argv[1] = "-addTestSuite";
    argv[2] = "MyTestSuite";
    argv[3] = 0;
    argv[4] = 0;
}

void run()
{
    cas::CmdLine cmdLine(argc, argv);

    CK(2 == cmdLine.args.size());
    CK("-addTestSuite" == cmdLine.args[0]);
    CK("MyTestSuite" == cmdLine.args[1]);
}

END_DEF



