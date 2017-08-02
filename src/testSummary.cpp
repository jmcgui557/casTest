#include "testSummary.h"

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
    out << "Test Summary:"
	<< "\n    Tests ran: " << total()
	<< "\n       Passed: " << passed_
	<< "\n      Skipped: " << skipped_
	<< "\n       Failed: " << failed_ << "\n\n";
}
