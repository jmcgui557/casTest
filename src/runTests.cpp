// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include "runTests.h"

#include "testCase.h"
#include "testLib.h"
#include "trace.h"

#include <stdexcept>

namespace cas
{
    bool runTest(cas::TestCase* test, size_t testNumber)
    {
        bool success(true);
        std::string errMsg("UNKNOWN err");

        test->setUp();

        try
        {
            test->run();
        }
        catch(const cas::TestCase::Error& x)
        {
	    success = false;
            errMsg = "Caught cas::Test::Error: ";
            errMsg += x.what();
        }
        catch(const std::exception& x)
        {
	    success = false;
            errMsg = "Caught std::exception: ";
            errMsg += x.what();
        }
        catch(...)
        {
	    success = false;
            errMsg = "Caught UNKNOWN EXCEPTION.";
        }
        
        cas_print((success ? "ok " : "not ok ") << testNumber << 
                  " - " << test->getName());

        if(!success)
        {
            cas_print("\t---");
            cas_print("\t" << errMsg);
            cas_print("\t---");
        }
        
        test->tearDown();

        return success;
    }

    size_t runTests(const std::vector<TestCase*>& tests)
    {
        std::vector<TestCase*>::const_iterator
            tb(tests.begin()),
            te(tests.end());
        
        size_t testCount(tests.size());

        if(0 < testCount)
            cas_print("1.." << testCount);

	size_t failCount(0);

	while(tb != te)
        {
            size_t testNumber(std::distance(tests.begin(), tb) + 1);
            bool success(runTest(*tb, testNumber));
          
            if(!success)
                ++failCount;
          
            ++tb;
        }
	
	return failCount;
    }

  size_t runTestsFromLibrary(const std::string& libname)
  {
    std::vector<TestCase*> tests;
    TestLib testLib(libname);

    cas_print("\ncasTest: Running tests from: " << libname);

    testLib.createTests(tests);

    if(0 == tests.size())
      throw std::runtime_error("No tests in library");

    size_t failCount(runTests(tests));

    testLib.destroyTests(tests);

    return failCount;
  }
}
