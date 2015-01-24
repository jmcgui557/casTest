// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAS may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include "testCase.h"

#include <algorithm>

namespace cas
{
    TestCase::Error::Error(const std::string& errMsg)
	: std::runtime_error(errMsg)
    {}

    TestCase::TestCase(const std::string& testName)
	: name_(testName)
    {}

    TestCase::~TestCase()
    {}
    /*
    const std::string& TestCase::getName() const
    {
	return name_;
    }
    */
    void TestCase::Assert(bool isTrue,
			  const std::string& errorMsg)
    {
	if(isTrue)
	    return;

	std::string em("Assertion FAILED: ");
	em += errorMsg;

	throw xTest(em);
    }

    void TestCase::setUp()
    {}

    void TestCase::tearDown()
    {}

    std::vector<TestCase*>& testContainer()
    {
        static std::vector<TestCase*> tests;

        return tests;
    }

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

