// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#include "cmdFactory.h"

#include "aboutCmd.h"
#include "addTestSuiteCmd.h"
#include "cmdLine.h"
#include "usageCmd.h"
#include "verCmd.h"
#include "trace.h"

#include <ostream>

namespace cas
{
    CastCmd* CastCmdFactory::create(const CmdLine& cmdLine,
				    std::ostream& out)
    {
	CastCmd* cmd(0);
	
	if('-' != cmdLine.args[0][0])
	    return cmd;
	
	if(0 == cmdLine.args[0].compare("-about"))
	    cmd = new AboutCmd(cmdLine, out);
	else if(0 == cmdLine.args[0].compare("-addTestSuite"))
	    cmd = new AddTestSuiteCmd(cmdLine);
	else if(0 == cmdLine.args[0].compare("-version"))
	    cmd = new VersionCmd(cmdLine, out);
	else
	    cmd = new UsageCmd(cmdLine, out);
	
	return cmd;
    }

}
