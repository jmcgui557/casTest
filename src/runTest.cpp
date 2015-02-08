// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAS may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include "runTest.h"

#include "testCase.h"
#include "trace.h"

#include <dlfcn.h>
#include <cerrno>
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

    LoadLibraryAndRunTests::Error::Error(const std::string& errString)
        : std::runtime_error(errString)
    {}

    const std::string
    LoadLibraryAndRunTests::FactoryFunctionName("createTests");

    const std::string
    LoadLibraryAndRunTests::DestructorFunctionName("destroyTests");

    LoadLibraryAndRunTests::LoadLibraryAndRunTests()
        : failCount_(0)
    {}

    int LoadLibraryAndRunTests::operator()(const std::string& libname)
    {
        void* libHandle(loadLibrary(libname));
        
        TestFactoryFunction createTests(mapFunction(libHandle,
                                                    FactoryFunctionName));
        TestFactoryFunction destroyTests(mapFunction(libHandle,
                                                     DestructorFunctionName));

        std::vector<TestCase*> tests;
        
        createTests(tests);

        cas_print("\ncasTest: Running tests from: " << libname);

        if(0 == tests.size())
            throw std::runtime_error("No tests in library");

        runTests(tests);
        destroyTests(tests);
        dlclose(libHandle);

        return failCount_;
    }

    void LoadLibraryAndRunTests::runTests(const std::vector<TestCase*>& tests)
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
            bool success(runTest(*tb, testNumber));
          
            if(!success)
                ++failCount_;
          
            ++tb;
        }
    }

    int LoadLibraryAndRunTests::getFailCount() const
    {
          return failCount_;
    }

    void* LoadLibraryAndRunTests::loadLibrary(const std::string& libname)
    {
        void* l(dlopen(libname.c_str(), RTLD_NOW));

        if(!l)
        {
            std::string msg("FAILED to loadLibrary: ");
            msg += dlerror();
            throw Error(msg);
        }

        return l;
    }

    TestFactoryFunction
    LoadLibraryAndRunTests::mapFunction(void* libHandle,
                                        const std::string& functionName)
    {
        TestFactoryFunction ff(
            reinterpret_cast<TestFactoryFunction>(
                dlsym(libHandle, functionName.c_str())));

        if(!ff)
        {
            std::string msg("FAILED to map factory function: ");
            msg += dlerror();
            throw Error(msg);
        }

        return ff;
    }
}
