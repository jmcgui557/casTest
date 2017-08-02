#ifndef TESTSUMMARY_H
#define TESTSUMMARY_H

#include <cstdlib>
#include <ostream>

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


#endif //TESTSUMMARY_H
