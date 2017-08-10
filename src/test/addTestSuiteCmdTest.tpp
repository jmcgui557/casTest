#include "testCase.h"
#include "trace.h"

#include "tsMakefile.h"
#include "fileFactory.h"
#include "../addTestSuiteCmd.cpp"
#include "cmdLine.h"

DEFINE_TEST(AddTestSuiteCmdCreatesTppSource)
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


