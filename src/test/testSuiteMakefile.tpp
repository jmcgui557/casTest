#include "testCase.h"

#include "tsMakefile.h"

#include <iostream>
#define dbg(msg) std::cout << msg << std::endl


#include <sstream>

DEFINE_BASE(MakefileTest)
TestSuiteMakefile m;
std::string expectedRecipe;

void setUp()
{
    expectedRecipe = "\t$(MAKE) -f myFirstTest.mak $@\n";
}

END_DEF

DEFINE_TEST_FROM(AddingGoalAddsTargetAllAndTargetWildcard, MakefileTest)
void run()
{
    m.addRecipe("myFirstTest");

    CK(expectedRecipe == m.getRecipe("all"));
    CK(expectedRecipe == m.getRecipe("%"));
}

END_DEF

DEFINE_TEST_FROM(AddingSubsequentGoalsAppendToRecipe, MakefileTest)
void setUp()
{
    MakefileTest::setUp();
    
    expectedRecipe += "\t$(MAKE) -f mySecondTest.mak $@\n";
}

void run()
{
    m.addRecipe("myFirstTest");
    m.addRecipe("mySecondTest");

    CK(expectedRecipe == m.getRecipe("all"));
    CK(expectedRecipe == m.getRecipe("%"));
}

END_DEF

DEFINE_TEST_FROM(AddingGoalTwiceResultsInASingleGoalInItsRecipe, MakefileTest)
void run()
{
    m.addRecipe("myFirstTest");
    m.addRecipe("myFirstTest");

    CK(expectedRecipe == m.getRecipe("all"));
    CK(expectedRecipe == m.getRecipe("%"));
}

END_DEF

DEFINE_TEST_FROM(OnConstructionTSMakefileReadsPassedIstreamForData, MakefileTest)
std::istream* s;
std::string data;
TestSuiteMakefile* mf;

void setUp()
{
    data =
	"all:\n"
	"\t$(MAKE) -f test1.mak $@\n"
	"\t$(MAKE) -f test2.mak $@\n"
	"\t$(MAKE) -f test3.mak $@\n"
	"\n"
	"%:\n"
	"\t$(MAKE) -f test1.mak $@\n"
	"\t$(MAKE) -f test2.mak $@\n"
	"\t$(MAKE) -f test3.mak $@\n"
	"\n";
	
    s = new std::istringstream(data);
    mf = new TestSuiteMakefile(*s);
}

void tearDown()
{
    delete s;
    delete mf;
}

void run()
{
    std::string expected("\t$(MAKE) -f test1.mak $@\n"
			 "\t$(MAKE) -f test2.mak $@\n"
			 "\t$(MAKE) -f test3.mak $@\n");

    CK(expected == mf->getRecipe("all"));
    CK(expected == mf->getRecipe("%"));
}

END_DEF

DEFINE_TEST_FROM(MakefileWritesTargetRecipesToStream, MakefileTest)
std::string expectedData;

void setUp()
{
    expectedData =
	"all:\n"
	"\t$(MAKE) -f test1.mak $@\n"
	"\t$(MAKE) -f test2.mak $@\n"
	"\t$(MAKE) -f test3.mak $@\n"
	"\n"
	"%:\n"
	"\t$(MAKE) -f test1.mak $@\n"
	"\t$(MAKE) -f test2.mak $@\n"
	"\t$(MAKE) -f test3.mak $@\n"
	"\n";

    m.addRecipe("test1");
    m.addRecipe("test2");
    m.addRecipe("test3");
}

void run()
{
    std::ostringstream out;

    m.write(out);

    CK(out.str() == expectedData);
}

END_DEF

//test output using mock ofstream
