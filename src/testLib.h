// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAS may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#ifndef TESTLIB_H
#define TESTLIB_H

#include <stdexcept>
#include <string>
#include <vector>

namespace cas
{
    struct TestCase;

    extern "C"
    {
        typedef void (*TestFactoryFunction)(std::vector<TestCase*>&);
    }

    struct TestLib
    {
        static const std::string FactoryFunctionName;
        static const std::string DestructorFunctionName;
        
        struct Error : public std::runtime_error
        {
            Error(const std::string& error);
            
        };

        TestLib(const std::string& libname);
        ~TestLib();

        void createTests(std::vector<TestCase*>& tests);
        void destroyTests(std::vector<TestCase*>& tests);

    private:
        void* loadLibrary(const std::string& libname);
        TestFactoryFunction mapFunction(void* libHandle,
                                        const std::string& functionName);

        void* libHandle_;
        TestFactoryFunction createTests_;
        TestFactoryFunction destroyTests_;
    };
}

#endif //RUNTEST_H
