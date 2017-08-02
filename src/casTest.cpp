// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
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
#include "testSummary.h"
#include "usage.h"

using namespace cas;

int reportResult(const TestSummary& sum)
{
    sum.write(std::cout);

    return sum.failed();
}

int runTests(const CmdLine& cmdLine)
{
    std::vector<std::string>::const_iterator
        beg(cmdLine.args.begin()),
        end(cmdLine.args.end());

    TestSummary sum;

    while(beg != end)
    {
        runTestsFromLibrary(*beg, sum);
        ++beg;
    }

    return reportResult(sum);
}

int main(int argc, const char* argv[])
{
    if(2 > argc)
        return usage();

    int failCount(0);

    try
    {
        CmdLine cmdLine(argc, argv);

        if(!CastCmd::executeCmd(cmdLine))
            failCount = runTests(cmdLine);
    }
    catch(const cas::TestCase::Error& x)
    {
        cas_error("CAUGHT cas::TestCase::Error: " << x.what());
        ++failCount;
    }
    catch(const std::exception& x)
    {
        cas_error("CAUGHT std::exception: " << x.what());
        ++failCount;
    }
    catch(...)
    {
        cas_error("CAUGHT UNKNOW execption");
        ++failCount;
    }

    return failCount;
}
