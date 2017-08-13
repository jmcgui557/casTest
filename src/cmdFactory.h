// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#ifndef CMDFACTORY_H
#define CMDFACTORY_H

#include <iostream>

namespace cas
{
    struct CastCmd;
    struct CmdLine;
    
    struct CastCmdFactory
    {
	static CastCmd* create(const CmdLine& cmdLine,
			       std::ostream& out = std::cout);
	
    private:
	//no objects
	~CastCmdFactory();
    };
}

#endif //CMDFACTORY_H
