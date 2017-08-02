// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#include "testCase.h"

#include <algorithm>
#include <cstdio>

namespace cas
{
    //OK, so this is a minor violation of the DRY principal,
    //but, this is meant for libcasTest.a and we get duplicate
    //symbol errors if we use createErrMsg() from casUtil.h
    std::string createErrorMsg(const std::string& errMsg,
                               const char* file,
                               size_t line)
    {
        char buff[256];
        snprintf(buff,
                 256,
                 "%s: %s:%lu",
                 errMsg.c_str(),
                 file,
                 line);
        
        return std::string(buff);
    }

    TestCase::Error::Error(const std::string& errMsg,
                           const char* file,
                           size_t line)
        : std::runtime_error(createErrorMsg(errMsg,
                                            file,
                                            line))
    {}

    TestCase::TestCase(const std::string& testName,
                       bool skip)
        : name_(testName),
          skip_(skip)
    {}

    TestCase::~TestCase()
    {}

    void TestCase::Assert(bool isTrue,
                          const std::string& errorMsg)
    {
        if(isTrue)
            return;

        std::string em("Assertion FAILED: ");
        em += errorMsg;
        em += "\nWARNING: This version of Assert() has been deprecated \n"
            "           please use the CK() macro.\n";

        throw Error(em, __FILE__, __LINE__);
    }

    void TestCase::Assert(bool isTrue,
                          const std::string& expectedConditionString,
                          const char* file,
                          size_t line)
    {
        if(isTrue)
            return;

        std::string em("Assertion(");
        em += expectedConditionString;
        em += ") FAILED";

        throw Error(em, file, line);
    }

    void TestCase::setUp()
    {}

    void TestCase::tearDown()
    {}

    struct DeleteTest
    {
        void operator()(TestCase* test) const
        {
            delete test;
        }
    };
}

//loadable destructor function
void destroyTests(std::vector<cas::TestCase*>& tests)
{
    std::for_each(tests.begin(),
                  tests.end(),
                  cas::DeleteTest());
}

