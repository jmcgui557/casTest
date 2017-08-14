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

//mocks
#include "castUtil.h"
#include "cmdFactory.h"

//code under test
#include "../castCmdExec.cpp"

DEFINE_BASE(ExecTest)
int argc;
const char* argv[3];

END_DEF

DEFINE_TEST_FROM(ExecuteCmdReturnsFalseIfCmdCantBeCreated, ExecTest)
void setUp()
{
    argc = 1;
    argv[0] = "casTest";
    argv[1] = 0;

    cas::GenericCmd::result = true;
}

void run()
{
    cas::CmdLine cmdLine(argc, argv);

    bool result(cas::executeCmd(cmdLine));

    CK(false == result);
}
END_DEF

DEFINE_TEST_FROM(ExecuteCmdReturnsResultOfCmdExec, ExecTest)
void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-genCommand";
    argv[2] = 0;
}

void testTrueResult()
{
    cas::GenericCmd::result = true;

    cas::CmdLine cmdLine(argc, argv);

    bool result(cas::executeCmd(cmdLine));

    CK(true == result);
}

void testFalseResult()
{
    cas::GenericCmd::result = false;

    cas::CmdLine cmdLine(argc, argv);

    bool result(cas::executeCmd(cmdLine));

    CK(false == result);
}

void run()
{
    testTrueResult();
    testFalseResult();
}

END_DEF

