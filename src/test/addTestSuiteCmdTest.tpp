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

#include "castUtil.h"
#include "tsMakefile.h"
#include "fileFactory.h"
#include "cmdLine.h"

//code under test
#include "../addTestSuiteCmd.cpp"

DEFINE_BASE(ATSCmdTest)
int argc;
const char* argv[4];
cas::CmdLine* cmdLine;
std::string expected;
void setUp()
{
    argc = 3;
    argv[0] = "casTest";
    argv[1] = "-addTestSuite";
    argv[2] = "myNewTest";
    argv[3] = 0;

    cmdLine = new cas::CmdLine(argc, argv);

    cas::CastUtil::castDir = "castDir";
    cas::CastUtil::createResult = true;
}

void tearDown()
{
    delete cmdLine;

    cas::FileFactory::reset();
}

END_DEF

DEFINE_TEST_FROM(AddTestSuiteCmdCreatesTppSource, ATSCmdTest)
void setUp()
{
    ATSCmdTest::setUp();

    expected =
        "#include \"testCase.h\"\n\n"
        "DEFINE_TEST(SanityTest)\n"
        "void run()\n"
        "{\n"
        "    bool val(false);\n\n"
        "    CK(true == val);\n"
        "}\n"
        "END_DEF\n\n\n";
}

void run()
{
    cas::AddTestSuiteCmd cmd(*cmdLine);

    cmd.exec();

    CK(expected == cas::FileFactory::getOutput("myNewTest.tpp"));
}
END_DEF

DEFINE_TEST_FROM(AddTestSuiteCmdThrowsIfCAST_DIRIsNotDefined, ATSCmdTest)
void run()
{
    cas::CastUtil::castDir = std::string();
    
    EXPECT_THROW(cas::AddTestSuiteCmd cmd(*cmdLine), cas::CastCmd::Error);
}

END_DEF

DEFINE_TEST_FROM(AddTestSuiteCmdThrowsIfTooFewArgs, ATSCmdTest)
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
    cas::CastUtil::castDir = std::string();

    EXPECT_THROW(cas::AddTestSuiteCmd cmd(*cmdLine), cas::CastCmd::Error);
}

END_DEF

DEFINE_TEST_FROM(AddTestSuiteCmdThrowsIfMakeFileTemplateCopyFails, ATSCmdTest)
void run()
{
    cas::CastUtil::createResult = false;
    cas::AddTestSuiteCmd cmd(*cmdLine);

    EXPECT_THROW(cmd.exec(), cas::CastCmd::Error);
}

END_DEF
