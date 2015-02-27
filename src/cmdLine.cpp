// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include "cmdLine.h"

namespace cas
{
    CmdLine::CmdLine(int argc, const char* argv[])
    {
        if(2 > argc)
            return;
        
        int a(1);
        
        while(a < argc)
        {
	    args.push_back(argv[a]);
            ++a;
        }
    }
}
