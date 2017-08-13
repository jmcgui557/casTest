// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#ifndef ADDTESTSUITECMD_H
#define ADDTESTSUITECMD_H

#include "castCmd.h"

#include <string>

namespace cas
{
    struct CmdLine;
    
    struct AddTestSuiteCmd : CastCmd
    {
        AddTestSuiteCmd(const CmdLine& cmdLine)
	    : CastCmd(cmdLine)
	{}
        
        bool exec()
	{
	    return true;
	}
        
    private:
    };
} //namespace cas

#endif //ADDTESTSUITECMD_H

