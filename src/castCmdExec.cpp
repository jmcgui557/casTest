// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#include "castCmdExec.h"

#include "castCmd.h"
#include "cmdFactory.h"

#include <memory>

namespace cas
{
    std::unique_ptr<CastCmd> createCommand(const cas::CmdLine& cmdLine)
    {
        return std::unique_ptr<CastCmd>(CastCmdFactory::create(cmdLine));
    }

    bool executeCmd(const cas::CmdLine& cmdLine)
    {
        std::unique_ptr<CastCmd> cmd(createCommand(cmdLine));
        
        if(!cmd.get())
            return false;
        
        return cmd->exec();
    }
}
  
