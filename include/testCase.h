// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAST may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2013-2015, 2017 Randall Lee White

#ifndef CAS_TESTCASE_H
#define CAS_TESTCASE_H

#include <stdexcept>
#include <string>
#include <vector>

namespace cas
{
    struct TestCase
    {
        struct Error : std::runtime_error
        {
	  Error(const std::string& errMsg,
		const char* file,
		size_t line);
        };

        TestCase(const std::string& testName);
        virtual ~TestCase();

        virtual void setUp();
        virtual void tearDown();
        virtual void run() = 0;

        const std::string& getName() const
        {
            return name_;
        }

	//deprecated.  better to use CK
        static void Assert(bool isTrue,
                           const std::string& errorMsg);

	static void Assert(bool isTrue,
			   const std::string& errorMsg,
			   const char* file,
			   size_t line);

        static void addTest(TestCase*);

    private:
	
        std::string name_;
    };

#define CK(cond) Assert(cond, #cond, __FILE__, __LINE__)

#define DEFINE_TEST(name)                 \
    struct name : cas::TestCase           \
    {                                     \
        name()                            \
            : TestCase(#name)             \
        {}

#define DEFINE_BASE(name)                 \
    struct name : cas::TestCase           \
    {                                     \
        name()                            \
            : TestCase(#name)             \
        {}                                \
                                          \
        name(const std::string& testName) \
            : TestCase(testName)          \
        {}

#define DEFINE_TEST_FROM(derived, base) \
    struct derived : base               \
    {                                   \
        derived()                       \
            : base(#derived)            \
        {}

#define END_DEF };

}

extern "C"
{
    //loadable destructor function
    void destroyTests(std::vector<cas::TestCase*>& tests);
}


#endif 
