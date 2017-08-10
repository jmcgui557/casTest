// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#ifndef CASTCMD_H
#define CASTCMD_H

#include <stdexcept>
#include <string>

namespace cas
{
    struct CmdLine;

    struct CastCmd
    {
        struct Error : std::runtime_error
        {
	    Error(const std::string& error,
		  const char* file,
		  size_t line);
	};

#define xCastCmd(msg) cas::CastCmd::Error(msg, __FILE__, __LINE__)
    
        CastCmd(const CmdLine& cmdLine);
        virtual ~CastCmd();
 
        virtual bool exec() = 0;

    protected:
        const std::string& name() const;

    private:
        std::string name_;
    };
}

#endif
