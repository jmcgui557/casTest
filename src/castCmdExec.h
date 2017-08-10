// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#ifndef CASTCMDEXEC_H
#define CASTCMDEXEC_H

#include "cmdLine.h"

namespace cas
{
    //Returns true if a command was created from the passed args.
    //Calls exec() on the created command.  CastCmd objects may
    //throw CastCmd::Error on failure.
    bool executeCmd(const CmdLine& cmdLine);
}

#endif //CASTCMDEXEC_H
