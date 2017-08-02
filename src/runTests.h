// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAST may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#ifndef RUNTEST_H
#define RUNTEST_H

#include <string>

struct TestSummary;

namespace cas
{
    //returns number of failed tests
    void runTestsFromLibrary(const std::string& libname,
                             TestSummary& sum);
}

#endif //RUNTEST_H
