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
#include "castUtil.h" //mock

//code under test
#include "../verCmd.cpp"
#include "../version.cpp"

#include <sstream>

DEFINE_TEST(VerCmdWritesCurrentVersionToStream)
int argc;
const char* argv[3];

void setUp()
{
    argc = 2;

    argv[0] = "casTest";
    argv[1] = "-version";
    argv[2] = 0;
}

void run()
{
    cas::CmdLine cmdLine(argc, argv);
    std::ostringstream out;
    
    cas::VersionCmd ver(cmdLine, out);
    ver.exec();

    CK("1.0\n" == out.str());
}

END_DEF
