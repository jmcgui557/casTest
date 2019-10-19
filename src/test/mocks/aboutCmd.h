// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#ifndef ABOUTCMD_H
#define ABOUTCMD_H

#include "castCmd.h"

#include <iostream>

namespace cas
{
    struct CmdLine;
    
    struct AboutCmd : CastCmd
    {
        AboutCmd(const CmdLine& cmdLine,
                 std::ostream& out = std::cout)
            : CastCmd(cmdLine),
              out_(out)
        {}

        bool exec()
        {
            return true;
        }

    private:
        std::ostream& out_;
    };
}

#endif //ABOUTCMD_H
