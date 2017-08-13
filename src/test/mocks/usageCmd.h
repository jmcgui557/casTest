// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#ifndef USAGECD_H
#define USAGECD_H

#include "castCmd.h"

#include <iostream>

namespace cas
{
    struct CmdLine;
    
    struct UsageCmd : CastCmd
    {
        UsageCmd(const CmdLine& cmdLine,
                 std::ostream& out = std::cout)
	    : CastCmd(cmdLine),
              out_(out)
	{
	    if("-help" != name())
		setName("-usage");
	}
        
        bool exec()
	{
	    out_ << "USAGE:" << std::endl;
	    
	    return true;
	}

    private:
        std::ostream& out_;
    };
}
    
#endif //USAGECD_H
