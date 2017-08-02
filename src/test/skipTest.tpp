#include "testCase.h"

struct SkipTest : cas::TestCase
{
    SkipTest()
	: cas::TestCase("SkipTest", true)
    {}
    
    void run()
    {

    }

private:
};

@SKIP
DEFINE_TEST(SkippedTestIsReported_CheckManually)
void run()
{
    CK(false);
}

END_DEF
DEFINE_TEST(SkippedTestThrowsTestSkipped)
void run()
{
    bool success(false);
    SkipTest skipTest;
    
    try
    {
	skipTest.run_();
    }
    catch(const TestCase::TestSkipped& x)
    {
	success = true;
    }

    CK(success);
}
END_DEF


