// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAS may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#ifndef CMDLINE_H
#define CMDLINE_H

#include <string>
#include <vector>

namespace cas
{
    struct TestCase;
    
    struct CmdLine
    {
	CmdLine(int argc, const char* argv[]);
	
	std::vector<std::string> libraries; //essentially testSuits
    };
}

#endif //CMDLINE_H
