// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#include "usageCmd.h"

#include "cmdLine.h"
#include "usage.h"

namespace cas
{
    UsageCmd::UsageCmd(const cas::CmdLine& cmdLine,
		       std::ostream& out)
	: CastCmd(cmdLine),
	  out_(out)
    {
	if("-help" != name())
	    setName("-usage");
    }
	
    bool UsageCmd::exec()
    {
	if("-help" != name())
	    out_ << "casTest: UNRECOGNIZED command: " << name() << "\n";

	usage(out_);

	return true;
    }
}
    

