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

#include <string>
#include <sstream>

//code under test
#include "../aboutCmd.cpp"

DEFINE_TEST(AboutCmdPrintsGeneralInfo)
int argc;
const char* argv[3];
cas::CmdLine* cmdLine;

void setUp()
{
    argc = 2;
    argv[0] = "casTest";
    argv[1] = "-about";
    argv[2] = 0;

    cmdLine = new cas::CmdLine(argc, argv);
}

void tearDown()
{
    delete cmdLine;
}

void run()
{
    std::string expected("\nThank you for trying casTest.  "
                         "casTest is meant to be "
                         "\na clean and simple unit test framework.  "
                         "\nI hope you find it so....Randy"
                         "\n\n(C) 2015, 2017 Randall Lee White\n\n");
    
    std::ostringstream out;
    cas::AboutCmd about(*cmdLine, out);

    about.exec();

    CK(expected == out.str());
}
END_DEF


