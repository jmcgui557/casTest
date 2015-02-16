// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAS may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "trace.h"

#include "castCmd.h"
#include "cmdLine.h"
#include "runTests.h"
#include "testCase.h"

using namespace cas;

int usage()
{
    cas_print("USAGE:");
    cas_print("\tcasTest -newTest <testSuiteName> [makefileName]");
    cas_print("\tcasTest <testLib1> [<testLib2> <...testLibN>]");

    return -1;
}

int reportResult(int failCount)
{
    if(0 == failCount)
        cas_print("casTest: All tests PASSED.");
    else
        cas_print("casTest: " << failCount << " tests FAILED.");

    cas_print("");
    return failCount;
}

int runTests(const CmdLine& cmdLine)
{
    std::vector<std::string>::const_iterator
        beg(cmdLine.args.begin()),
        end(cmdLine.args.end());

    size_t failCount(0);

    while(beg != end)
    {
        failCount += runTestsFromLibrary(*beg);
	++beg;
    }

    return reportResult(failCount);
}

int main(int argc, const char* argv[])
{
    if(2 > argc)
        return usage();

    int failCount(0);

    try
    {
        CmdLine cmdLine(argc, argv);

	if(!CastCmd::execCommand(cmdLine))
	    failCount = runTests(cmdLine);
    }
    catch(const cas::TestCase::Error& x)
    {
        cas_error("CAUGHT cas::TestCase::Error: " << x.what());
        failCount = -1;
    }
    catch(const std::exception& x)
    {
        cas_error("CAUGHT std::exception: " << x.what());
        failCount = -1;
    }
    catch(...)
    {
        cas_error("CAUGHT UNKNOW execption");
        failCount = -1;
    }

    return failCount;
}
