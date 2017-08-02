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
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define print(msg) std::cout << msg << std::endl

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
    std::string cppFilename(tppFilename.begin(),
                            tppFilename.begin() + p);

    cppFilename += ".cpp";

    return cppFilename;
}

int tpp2cpp(const std::string& tppFilename)
{
    std::string cppFilename(getTargetFilename(tppFilename));

    print("tpp2cpp: " << tppFilename << " -> " << cppFilename);

    std::ifstream tppFile(tppFilename.c_str());
    std::ofstream cppFile(cppFilename.c_str());

    Tpp2Cpp converter(tppFile);

    converter.write(cppFile);

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
