// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#ifndef DYNLIBUTIL_H
#define DYNLIBUTIL_H

#include "testCase.h"

extern "C"
{
    void createTestsMock(std::vector<cas::TestCase*>&)
    {
        
    }
    void destroyTestsMock(std::vector<cas::TestCase*>&)
    {
        
    }
    
}

namespace cas
{
    extern "C"
    {
        typedef void (*TestFactoryFunctionMock)(std::vector<TestCase*>&);
    }

    struct DynLibUtil
    {
        static const int LD_NOW;
        static void* mock_dlhandleVal;
        static void* mock_dlsymVal;
        
        static int close(void* handle)
        {
            return 0;
        }
        
        static void* open(const char* filename,
                          int flags)
        {
            return mock_dlhandleVal;
        }
        
        static void* sym(void* handle,
                         const char* symbol)
        {
            if(0 == mock_dlsymVal)
                return mock_dlsymVal;
                
            if(symbol == "createTests")
                return reinterpret_cast<void*>(createTests_);

            return reinterpret_cast<void*>(destroyTests_);
        }

        static const char* error()
        {
            static const char* err("error");
            return err;
        }

        static TestFactoryFunctionMock createTests_;
        static TestFactoryFunctionMock destroyTests_;

    private:
        //no objects
        ~DynLibUtil();
    };

    const int DynLibUtil::LD_NOW(2);
    void* DynLibUtil::mock_dlhandleVal((void*)0x12345678);
    void* DynLibUtil::mock_dlsymVal((void*)0x87654321);
    TestFactoryFunctionMock DynLibUtil::createTests_ = createTestsMock;
    TestFactoryFunctionMock DynLibUtil::destroyTests_ = destroyTestsMock;
}

#endif //DYNLIBUTIL_H
