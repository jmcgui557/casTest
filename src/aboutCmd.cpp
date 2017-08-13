// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#include "aboutCmd.h"

#include "cmdLine.h"

namespace cas
{
    AboutCmd::AboutCmd(const CmdLine& cmdLine,
		       std::ostream& out)
	: CastCmd(cmdLine),
	  out_(out)
    {}

    bool AboutCmd::exec()
    {
	out_
	    << "\nThank you for trying casTest.  casTest is meant to be "
	    << "\na clean and simple unit test framework.  "
	    << "\nI hope you find it so....Randy"
	    << "\n\n(C) 2015, 2017 Randall Lee White\n"
	    << std::endl;
	
	return true;
    }
}

