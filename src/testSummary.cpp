// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAST poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
//
// Copyright (c) 2017 Randall Lee White

#include "testSummary.h"

namespace cas
{
    TestSummary::TestSummary()
        : passed_(0),
          skipped_(0),
          failed_(0)
    {}
    
    void TestSummary::addResult(Result res)
    {
        switch(res)
        {
            case PASS:
                ++passed_;
                break;
                
            case SKIP:
                ++skipped_;
                break;
                
            case FAIL:
                ++failed_;
                break;
                
            default:
                ;
        }
    }
    
    size_t TestSummary::total() const
    {
        return passed_ +
            skipped_ +
            failed_;
    }
    
    size_t TestSummary::passed() const
    {
        return passed_;
    }
    
    size_t TestSummary::skipped() const
    {
        return skipped_;
    }
    
    size_t TestSummary::failed() const
    {
        return failed_;
    }
    
    void TestSummary::write(std::ostream& out) const
    {
        out << "\nSummary:"
            << "\n    Tests ran: " << total()
            << "\n       Passed: " << passed_
            << "\n      Skipped: " << skipped_
            << "\n       Failed: " << failed_ << "\n\n";
    }
}
