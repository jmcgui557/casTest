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

#include "castCmd.h"
#include "cmdLine.h"

#include <iostream>

namespace cas
{
    struct GenericCmd : CastCmd
    {
	static bool result;
	
	GenericCmd(const CmdLine& cmdLine)
	    : CastCmd(cmdLine)
	{}
	
	bool exec()
	{
	    return result;
	}
    };

    bool GenericCmd::result = true;
    
    struct CastCmdFactory
    {
	static CastCmd* create(const CmdLine& cmdLine,
			       std::ostream& out = std::cout)
	{
	    if(cmdLine.args.empty())
		return 0;

	    return new GenericCmd(cmdLine);
	}
	
    private:
	//no objects
	~CastCmdFactory();
    };
}

#endif //CMDFACTORY_H
