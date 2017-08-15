// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAST poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
//
// Copyright (c) 2017 Randall Lee White

#ifndef TESTSUMMARY_H
#define TESTSUMMARY_H

#include <cstdlib>
#include <ostream>

namespace cas
{
    struct TestSummary
    {
        enum Result
        {
            PASS,
            SKIP,
            FAIL
        };
        
        TestSummary();
        
        void addResult(Result res);
        
        size_t total() const;
        size_t passed() const;
        size_t skipped() const;
        size_t failed() const;
        
        void write(std::ostream& out) const;
        
    private:
        size_t passed_;
        size_t skipped_;
        size_t failed_;
    };
}


#endif //TESTSUMMARY_H
