// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include "testLib.h"

#include "testCase.h"
#include "trace.h"

#include <dlfcn.h>
#include <cerrno>
#include <stdexcept>

namespace cas
{
    TestLib::Error::Error(const std::string& errString)
        : std::runtime_error(errString)
    {}

    const std::string
    TestLib::FactoryFunctionName("createTests");

    const std::string
    TestLib::DestructorFunctionName("destroyTests");

  TestLib::TestLib(const std::string& libname)
      : libHandle_(0),
        createTests_(0),
	destroyTests_(0)
    {
        libHandle_ = loadLibrary(libname);
        createTests_ = mapFunction(libHandle_, FactoryFunctionName);
        destroyTests_ = mapFunction(libHandle_, DestructorFunctionName);
    }

    TestLib::~TestLib()
    {
        dlclose(libHandle_);
    }

    void TestLib::createTests(std::vector<TestCase*>& tests)
    {
        createTests_(tests);
    }

    void TestLib::destroyTests(std::vector<TestCase*>& tests)
    {
        destroyTests_(tests);
    }

    void* TestLib::loadLibrary(const std::string& libname)
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
    TestLib::mapFunction(void* libHandle,
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
