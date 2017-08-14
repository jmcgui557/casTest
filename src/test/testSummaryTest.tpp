// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#include "testCase.h"

//code under test
#include "../testSummary.cpp"

#include <string>
#include <sstream>

DEFINE_BASE(TestSummaryTest)
TestSummary sum;

END_DEF

DEFINE_TEST_FROM(NewTestSummaryReportsAllZeros, TestSummaryTest)
void run()
{
    CK(0 == sum.total());
    CK(0 == sum.passed());
    CK(0 == sum.failed());
    CK(0 == sum.skipped());
}
END_DEF

DEFINE_TEST_FROM(AddingResultIncrementsTotal, TestSummaryTest)
void run()
{
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::SKIP);
    sum.addResult(TestSummary::FAIL);

    CK(3 == sum.total());
}

END_DEF

DEFINE_TEST_FROM(AddingPassIncrementsPassCount, TestSummaryTest)
void run()
{
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::FAIL);
    sum.addResult(TestSummary::SKIP);

    CK(2 == sum.passed());
}

END_DEF

DEFINE_TEST_FROM(AddingSkipIncrementsSkipCount, TestSummaryTest)
void run()
{
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::FAIL);
    sum.addResult(TestSummary::SKIP);

    CK(1 == sum.skipped());

}

END_DEF

DEFINE_TEST_FROM(AddingFailIncrementsFailCount, TestSummaryTest)
void run()
{
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::FAIL);
    sum.addResult(TestSummary::SKIP);

    CK(1 == sum.failed());
}

END_DEF

DEFINE_TEST_FROM(SummaryIsWrittenToStream, TestSummaryTest)
void run()
{
    std::string expected("\nSummary:\n"
                         "    Tests ran: 7\n"
                         "       Passed: 4\n"
                         "      Skipped: 1\n"
                         "       Failed: 2\n"
                         "\n");

    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::SKIP);
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::PASS);
    sum.addResult(TestSummary::FAIL);
    sum.addResult(TestSummary::FAIL);

    std::ostringstream out;

    sum.write(out);

    CK(expected == out.str());
}

END_DEF
