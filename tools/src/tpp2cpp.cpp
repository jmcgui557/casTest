// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAST poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
//
// Copyright (c) 2017 Randall Lee White

#include "tpp2cpp.h"

#include <algorithm>

struct AppendTest
{
    AppendTest(std::ostream& out)
        : out_(out)
    {}

    void operator()(const std::string& test)
    {
        out_ << "        tests.push_back(new "
             << test << ");\n";
    }
    
private:
    std::ostream& out_;
};

std::string& Tpp2Cpp::skipTag()
{
    static std::string tag("@SKIP");

    return tag;
}

std::string& Tpp2Cpp::testTag()
{
    static std::string tag("DEFINE_TEST");

    return tag;
}

void Tpp2Cpp::setSkipTag(const std::string& tag)
{
    skipTag() = tag;
}

void Tpp2Cpp::setTestTag(const std::string& tag)
{
    testTag() = tag;
}

Tpp2Cpp::Tpp2Cpp(std::istream& in)
    : comment_(false),
      skip_(false),
      in_(in),
      tests_()
{}

void Tpp2Cpp::write(std::ostream& out)
{
    std::string line;
    while(std::getline(in_, line))
    {
        out << convertLine(line) << "\n";
    }

    appendTestFactory(out);
    
    out.flush();
}

void Tpp2Cpp::appendTestFactory(std::ostream& out)
{
    out << '\n'
        << "//----------------------------------------\n"
        << "#include <vector>\n"
        << '\n'
        << "extern \"C\"\n"
        << "{\n"
        << "    void createTests(std::vector<cas::TestCase*>& tests)\n"
        << "    {\n";

    std::for_each(tests_.begin(),
                  tests_.end(),
                  AppendTest(out));

    out << "    }\n"
        << "}\n\n";
}

std::string Tpp2Cpp::convertLine(const std::string& line)
{
    setCommentState(line);
    extractTest(line);

    if(std::string::npos != line.find(skipTag()))
        return skipOn(line);
    
    if(std::string::npos != line.find("END_DEF"))
        return skipOff(line);
    
    if(!skip_)
        return line;

    return convertLineIfNecessary(line);
}

void Tpp2Cpp::setCommentState(const std::string& line)
{
    if(true == comment_)
        setCommentFalseIfCloseFound(line);
    else
        setCommentTrueIfOpenFound(line);
}

void Tpp2Cpp::setCommentFalseIfCloseFound(const std::string& line)
{
    std::string::size_type p(line.rfind("*/"));

    if(std::string::npos == p)
        return;

    if(std::string::npos == line.find("/*", p))
        comment_ = false;
}

void Tpp2Cpp::setCommentTrueIfOpenFound(const std::string& line)
{
    std::string::size_type p(line.rfind("/*"));

    if(std::string::npos == p)
        return;

    if(std::string::npos == line.find("*/", p))
        comment_ = true;
}

std::string Tpp2Cpp::convertLineIfNecessary(const std::string& line)
{
    std::string::size_type p(line.find(testTag()));
    
    if(std::string::npos != p)
    {
        std::string newLine(line.begin(), line.begin() + p);
        newLine += "SKIP_TEST";

        if(std::string::npos != line.find("_FROM"))
            newLine += "_FROM";
        
        std::string::size_type r(line.find_first_of('(', p));
        
        newLine += std::string(line.begin() + r, line.end());
        
        return newLine;
    }

    return line;
}

void Tpp2Cpp::extractTest(const std::string& line)
{
    if(comment_)
        return;
    
    std::string::size_type p(line.find(testTag()));
    
    if(std::string::npos == p)
        return;
    
    if(!isTestEnabled(line, p))
        return;
    
    std::string::size_type b(line.find("("));
    std::string::size_type e(line.find_first_of(",)", b));
    
    std::string test(line.begin() + b + 1,
                     line.begin() + e);
    
    tests_.push_back(test);
}

bool Tpp2Cpp::isTestEnabled(const std::string& line,
                            std::string::size_type end)
{
    std::string segment(line.begin(),
                        line.begin() + end);
    
    if(std::string::npos != segment.find("//"))
        return false;
    
    std::string::size_type p(segment.find("/*"));
    
    if(std::string::npos == p)
        return true;
    
    return std::string::npos != segment.find("*/");
}
        

std::string Tpp2Cpp::skipOn(const std::string& line)
{
    skip_ = true;
        
    std::string newLine("//");
    newLine += line;
    
    return newLine;
}

std::string Tpp2Cpp::skipOff(const std::string& line)
{
    skip_ = false;

    return line;
}

