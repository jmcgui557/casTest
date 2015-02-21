#include "testCase.h"

DEFINE_TEST(SanityTest)
void run()
{
    bool val(false);

    Assert(val,
           "Please change val to true,  and try again.");
}
END_DEF


