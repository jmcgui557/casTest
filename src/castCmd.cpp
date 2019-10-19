// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#include "castCmd.h"

#include "castUtil.h"
#include "cmdLine.h"

namespace cas
{
    CastCmd::Error::Error(const std::string& err,
                          const char* file,
                          size_t line)
        : std::runtime_error(createErrMsg(err, file, line))
    {}

    CastCmd::CastCmd(const CmdLine& cmdLine)
      : name_()
    {
        if(!cmdLine.args.empty())
            name_ = cmdLine.args[0];
    }

    CastCmd::~CastCmd()
    {}

    const std::string& CastCmd::name() const
    {
        return name_;
    }

    void CastCmd::setName(const std::string& name)
    {
        name_ = name;
    }
}
