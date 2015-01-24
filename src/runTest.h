// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAS may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#ifndef RUNTEST_H
#define RUNTEST_H

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

    struct LoadLibraryAndRunTests
    {
        static const std::string FactoryFunctionName;
        static const std::string DestructorFunctionName;
        
        struct Error : public std::runtime_error
        {
            Error(const std::string& error);
            
        };

        LoadLibraryAndRunTests();
        
        //returns number of tests which failed
        int operator()(const std::string& libname);
        int getFailCount() const;
        
    private:
        void runTests(const std::vector<TestCase*>& tests);
        
        void* loadLibrary(const std::string& libname);
        TestFactoryFunction mapFunction(void* libHandle,
                                        const std::string& functionName);

        int failCount_;
    };
}

#endif //RUNTEST_H
