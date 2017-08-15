// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAST poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
//
// Copyright (c) 2017 Randall Lee White

#include "testCase.h"

#include <sstream>

#include <iostream>

#include "tpp2cpp.h"

DEFINE_TEST(DEFINE_TESTbecomesSKIP_TESTwhenTestIsSkipped)

void run()
{
    std::string tppData("#include testCase.h\n"
                        "\n"
                        "DEFINE_TEST(TestOne)\n"
                        "void run()\n"
                        "{\n"
                        "}\n"
                        "END_DEF\n"
                        "\n"
                        "@SKIP\n"
                        "DEFINE_TEST(TestTwo)\n"
                        "void run()\n"
                        "{\n"
                        "}\n"
                        "END_DEF\n"
                        "\n"
                        "/*\n"
                        "DEFINE_TEST(TestThree)\n"
                        "void run()\n"
                        "{\n"
                        "}\n"
                        "END_DEF\n"
                        "*/\n"
                        "\n"
                        "//DEFINE_TEST(TestFour)\n"
                        "//void run()\n"
                        "//{\n"
                        "//}\n"
                        "//END_DEF\n"
                        "\n"
                        "/*Comment before test*/DEFINE_TEST(TestFive)\n"
                        "void run()\n"
                        "{\n"
                        "}\n"
                        "END_DEF\n"
                        "\n"
                        "@SKIP\n"
                        "DEFINE_TEST_FROM(TestSix, BaseTest)\n"
                        "void run()\n"
                        "{\n"
                        "}\n"
                        "END_DEF\n"
                        "\n"
        );

    std::string expected("#include testCase.h\n"
                         "\n"
                         "DEFINE_TEST(TestOne)\n"
                         "void run()\n"
                         "{\n"
                         "}\n"
                         "END_DEF\n"
                         "\n"
                         "//@SKIP\n"
                         "SKIP_TEST(TestTwo)\n"
                         "void run()\n"
                         "{\n"
                         "}\n"
                         "END_DEF\n"
                         "\n"
                         "/*\n"
                         "DEFINE_TEST(TestThree)\n"
                         "void run()\n"
                         "{\n"
                         "}\n"
                         "END_DEF\n"
                         "*/\n"
                         "\n"
                         "//DEFINE_TEST(TestFour)\n"
                         "//void run()\n"
                         "//{\n"
                         "//}\n"
                         "//END_DEF\n"
                         "\n"
                         "/*Comment before test*/DEFINE_TEST(TestFive)\n"
                         "void run()\n"
                         "{\n"
                         "}\n"
                         "END_DEF\n"
                         "\n"
                         "//@SKIP\n"
                         "SKIP_TEST_FROM(TestSix, BaseTest)\n"
                         "void run()\n"
                         "{\n"
                         "}\n"
                         "END_DEF\n"
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
                         "        tests.push_back(new TestFive);\n"
                         "        tests.push_back(new TestSix);\n"
                         "    }\n"
                         "}\n"
                         "\n");

    std::istringstream tppFile(tppData);
    std::ostringstream cppFile;

    Tpp2Cpp tpp2cpp(tppFile);

    tpp2cpp.write(cppFile);

    CK(expected == cppFile.str());
}
END_DEF
