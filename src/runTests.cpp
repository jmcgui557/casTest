// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#include "runTests.h"

#include "testCase.h"
#include "testLib.h"
#include "testSummary.h"
#include "trace.h"

#include <stdexcept>

namespace cas
{
    std::string resultStr[] = {"ok ",
                               "skipped ",
                               "not ok "};
    
    void runTest(cas::TestCase* test,
                 size_t testNumber,
                 TestSummary& sum)
    {
        TestSummary::Result result(TestSummary::PASS);
        std::string errMsg("UNKNOWN err");

        test->setUp();

        try
        {
            test->run_();
        }
        catch(const cas::TestCase::Error& x)
        {
            result = TestSummary::FAIL;
            errMsg = "Caught cas::Test::Error: ";
            errMsg += x.what();
        }
        catch(const cas::TestCase::TestSkipped& x)
        {
            result = TestSummary::SKIP;
        }
        catch(const std::exception& x)
        {
            result = TestSummary::FAIL;
            errMsg = "Caught std::exception: ";
            errMsg += x.what();
        }
        catch(...)
        {
            result = TestSummary::FAIL;
            errMsg = "Caught UNKNOWN EXCEPTION.";
        }

        sum.addResult(result);
        
        cas_print(resultStr[result] << testNumber <<
                  " - " << test->getName());

        if(TestSummary::FAIL == result)
        {
            cas_print("\t---");
            cas_print("\t" << errMsg);
            cas_print("\t---");
        }
        
        test->tearDown();
    }

    void runTests(const std::vector<TestCase*>& tests,
                  TestSummary& sum)
    {
        std::vector<TestCase*>::const_iterator
            tb(tests.begin()),
            te(tests.end());
        
        size_t testCount(tests.size());

        if(0 < testCount)
            cas_print("1.." << testCount);

        while(tb != te)
        {
            size_t testNumber(std::distance(tests.begin(), tb) + 1);

            runTest(*tb, testNumber, sum);
            ++tb;
        }
    }

    void runTestsFromLibrary(const std::string& libname,
                             TestSummary& sum)
    {
        std::vector<TestCase*> tests;
        TestLib testLib(libname);

        cas_print("\ncasTest: Running tests from: " << libname);

        testLib.createTests(tests);

        if(0 == tests.size())
            throw std::runtime_error("No tests in library");

        runTests(tests, sum);

        testLib.destroyTests(tests);
    }
}
