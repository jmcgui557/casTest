// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAST poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
//
// Copyright (c) 2017 Randall Lee White
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define print(msg) std::cout << msg << std::endl

struct WriteLines
{
    WriteLines(std::ofstream& file)
    	: file_(file)
    {}

    void operator()(const std::string& line)
    {
	file_ << line << std::endl;
    }

private:
    std::ofstream& file_;
};

struct Tpp2Cpp
{
    Tpp2Cpp(std::vector<std::string>& cppLines,
	          std::vector<std::string>& tests)
	: skipping_(false),
	  cppLines_(cppLines),
	  tests_(tests)
    {}

    void operator()(const std::string& line)
    {
	cppLines_.push_back(tppLine2CppLine(line));
    }

private:
    std::string tppLine2CppLine(const std::string& line)
    {
	if(std::string::npos != line.find("@SKIP"))
	    return skipNextTest(line);

	if(skipping_)
	    return disabledLine(line);
	    
	extractTest(line);
	
	return line;
    }

    std::string disabledLine(const std::string& line)
    {
	std::string dl("//");
	dl += line;

	if(std::string::npos != line.find("END_DEF"))
	    skipping_ = false;

	return dl;
    }
    
    std::string skipNextTest(const std::string& line)
    {
	skipping_ = true;

	std::string l("//");
	l += line;

	return l;
    }
    
    void extractTest(const std::string& line)
    {
	if(std::string::npos == line.find("DEFINE_TEST"))
	    return;

	std::string::size_type b(line.find("("));
	std::string::size_type e(line.find_first_of(",)", b));

	std::string test(line.begin() + b + 1,
			      line.begin() + e);

	tests_.push_back(test);
    }

    bool skipping_;
    std::vector<std::string>& cppLines_;
    std::vector<std::string>& tests_;
};

int usage()
{
    print("USAGE:");
    print("\ttpp2cpp <tppFilename>");

    return -1;
}

bool fileExists(const std::string& fname)
{
    std::ifstream f(fname.c_str());

    return f.good();
}

bool isInputValid(int argc, char* argv[])
{
    if(2 < argc)
	return false;

    std::string fname(argv[1]);
    std::string::size_type p(fname.rfind(".tpp"));
    
    return 4 == fname.size() - p;
}

std::string getTargetFilename(const std::string& tppFilename)
{
    std::string::size_type p(tppFilename.rfind(".tpp"));
    std::string cppFilename(	tppFilename.begin(),
				        tppFilename.begin() + p);

    cppFilename += ".cpp";

    return cppFilename;
}

void collectTppLines(const std::string& tppFilename,
                               std::vector<std::string>& tppLines)
{
    std::ifstream tppFile(tppFilename.c_str());
    
    std::string line;
    while(std::getline(tppFile, line))
	tppLines.push_back(line);
}

struct AppendTest
{
    AppendTest(std::vector<std::string>& lines)
	: lines_(lines)
    {}

    void operator()(const std::string& test)
    {
	std::string tline("        tests.push_back(new ");
	tline += test;
	tline += ");";
	
	lines_.push_back(tline);
    }

private:
    std::vector<std::string>& lines_;
};

void appendTests(std::vector<std::string>& testLines,
		           const std::vector<std::string>& tests)
{
    testLines.push_back("");
    testLines.push_back("//------------------------------------------");
    testLines.push_back("#include <vector>");

    testLines.push_back("");
    testLines.push_back("extern \"C\"");
    testLines.push_back("{");
    testLines.push_back("    void createTests(std::vector<cas::TestCase*>& tests)");
    testLines.push_back("    {");

    std::for_each(tests.begin(),
		        tests.end(),
		        AppendTest(testLines));

    testLines.push_back("    }");
    testLines.push_back("}");
    testLines.push_back("");
}

void transformTppLines2CppLines(const std::vector<std::string>& tppLines,
			                          std::vector<std::string>& cppLines)
{
    std::vector<std::string> tmp;
    std::vector<std::string> tests;
    
    std::for_each(tppLines.begin(),
		        tppLines.end(),
		        Tpp2Cpp(tmp, tests));

    appendTests(tmp,
		        tests);
    
    tmp.swap(cppLines);
}

int tpp2cpp(const std::string& tppFilename)
{
    std::string cppFilename(getTargetFilename(tppFilename));
    std::vector<std::string> tppLines;

    collectTppLines(tppFilename, tppLines);

    std::vector<std::string> cppLines;

    transformTppLines2CppLines(tppLines,
			                       cppLines);

    std::ofstream cppFile(cppFilename.c_str());
    
    std::for_each(cppLines.begin(),
		        cppLines.end(),
		        WriteLines(cppFile));

    return 0;
}

int main(int argc, char* argv[])
{
    if(!isInputValid(argc, argv))
	return usage();

    std::string fname(argv[1]);
    
    if(!fileExists(fname))
    {
	print("Error: Can't find file: " << fname);
	return usage();
    }

    return tpp2cpp(fname);
}
