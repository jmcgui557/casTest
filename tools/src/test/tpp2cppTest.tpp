#include "testCase.h"

#include <sstream>

#include <iostream>

#include "tpp2Cpp.h"

@SKIP
DEFINE_TEST(SkipTestCheckOutputManually)
void run()
{


}

END_DEF

DEFINE_TEST(DEFINE_TESTbecomesSKIP_TESTwhenTestIsSkipped)
void run()
{
    std::string tppData("#include testCase.h\n"
			"\n"
			"DEFINE_TST(TestOne)\n"
			"void run()\n"
			"{\n"
			"}\n"
			"END_DEF\n"
			"\n"
			"@SKP\n" 
			"DEFINE_TST(TestTwo)\n"
			"void run()\n"
			"{\n"
			"}\n"
			"END_DEF\n"
			"\n"
			"/*\n"
			"DEFINE_TST(TestThree)\n"
			"void run()\n"
			"{\n"
			"}\n"
			"END_DEF\n"
			"*/\n"
			"\n"
			"//DEFINE_TST(TestOne)\n"
			"//void run()\n"
			"//{\n"
			"//}\n"
			"//END_DEF\n"
			"\n");

    std::string expected("#include testCase.h\n"
			"\n"
			"DEFINE_TST(TestOne)\n"
			"void run()\n"
			"{\n"
			"}\n"
			"END_DEF\n"
			"\n"
			"//@SKP\n"
			"SKIP_TEST(TestTwo)\n"
			"void run()\n"
			"{\n"
			"}\n"
			"END_DEF\n"
			"\n"
			"/*\n"
			"DEFINE_TST(TestThree)\n"
			"void run()\n"
			"{\n"
			"}\n"
			"END_DEF\n"
			"*/\n"
			"\n"
			"//DEFINE_TST(TestOne)\n"
			"//void run()\n"
			"//{\n"
			"//}\n"
			"//END_DEF\n"
			 "\n"
			 "\n"
			 "//----------------------------------------\n"
			 "#include <vector>\n"
			 "\n"
			 "extern \"C\"\n"
			 "{\n"
			 "    void createTests("
			 "std::vector<cas::TestCase*>& tests)\n"
			 "    {\n"
			 "        tests.push_back(new TestOne);\n"
			 "        tests.push_back(new TestTwo);\n"
			 "    }\n"
			 "}\n"
			 "\n");

    std::istringstream tppFile(tppData);
    std::ostringstream cppFile;

    //We change the skip and test
    //tags to allow us to test ourselves.
    Tpp2Cpp::setSkipTag("@SKP");
    Tpp2Cpp::setTestTag("DEFINE_TST");
    
    Tpp2Cpp tpp2cpp(tppFile);

    tpp2cpp.write(cppFile);

    CK(expected == cppFile.str());
}
END_DEF


