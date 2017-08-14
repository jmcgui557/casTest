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

//code under test
#include "../castCmd.cpp"

struct DoNothing : cas::CastCmd
{
    DoNothing(const cas::CmdLine& cmdLine)
        : CastCmd(cmdLine)
    {}
    
    bool exec()
    {
        return true;
    }
};

DEFINE_TEST(CastCmdNameIsInitializedFromCmdLine)
int argc;
const char* argv[3];
cas::CmdLine* cmdLine;

void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-doNothing";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void tearDown()
{
    delete cmdLine;
}

void run()
{
    DoNothing doNothing(*cmdLine);

    CK("-doNothing" == doNothing.name());
}
END_DEF

DEFINE_TEST(CastCmd_ErrorContainsErrMsgFileAndLineNumer)
void run()
{
    cas::CastCmd::Error err("My error",
                            "somefile.cpp",
                            123);

    std::string expected("ERROR [somefile.cpp(123)]: My error");
    
    CK(expected == err.what());

}

END_DEF

struct DerivedCmd : cas::CastCmd
{
    DerivedCmd(const cas::CmdLine& cmdLine)
        : cas::CastCmd(cmdLine)
    {
        setName("DerivedCmd");
    }

    bool exec()
    {
        return true;
    }

};

DEFINE_TEST(DerivedCmdCanSetItsName)
int argc;
const char* argv[3];
cas::CmdLine* cmdLine;

void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-inValid";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void tearDown()
{
    delete cmdLine;
}

void run()
{
    DerivedCmd cmd(*cmdLine);

    CK("DerivedCmd" == cmd.name());
}

END_DEF


