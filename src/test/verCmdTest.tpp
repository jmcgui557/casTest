#include "testCase.h"

#include "cmdLine.h"
#include "verCmd.h"

#include <sstream>

#include <iostream>
#define dbg(msg) std::cout << msg << std::endl

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

    dbg("ver: [" << out.str() << "]");

    CK("1.0\n" == out.str());

}

END_DEF
