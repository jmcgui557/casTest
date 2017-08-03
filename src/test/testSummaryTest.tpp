#include "testCase.h"

#include "testSummary.h"

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
