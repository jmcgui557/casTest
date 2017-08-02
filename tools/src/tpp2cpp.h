// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAST poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
//
// Copyright (c) 2017 Randall Lee White

#ifndef TPP2CPP_H
#define TPP2CPP_H

#include <iostream>
#include <string>
#include <vector>

struct TestCase;

struct Tpp2Cpp
{
    static void setSkipTag(const std::string& tag);
    static void setTestTag(const std::string& tag);
    
    Tpp2Cpp(std::istream& in);
    
    void write(std::ostream& out);

private:
    void appendTestFactory(std::ostream& out);
    
    std::string convertLine(const std::string& line);
    std::string convertLineIfNecessary(const std::string& line);
    
    void extractTest(const std::string& line);

    bool isTestEnabled(const std::string& line,
                       std::string::size_type end);

    void setCommentState(const std::string& line);
    void setCommentFalseIfCloseFound(const std::string& line);
    void setCommentTrueIfOpenFound(const std::string& line);
    
    std::string skipOn(const std::string& line);
    std::string skipOff(const std::string& line);

    static std::string& skipTag();
    static std::string& testTag();
    
    bool comment_;
    bool skip_;
    std::istream& in_;
    std::vector<std::string> tests_;
};

#endif //TPP2CPP_H
