#ifndef CASTUTIL_H
#define CASTUTIL_H
// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015, 2017 Randall Lee White

#include <iostream>

#include <cstdlib>
#include <cstdio>

namespace cas
{
    struct CastUtil
    {
	
	static bool createResult;
	static std::string castDir;
    };

    bool CastUtil::createResult = true;
    std::string CastUtil::castDir("castDir");

    std::string createErrMsg(const std::string& errMsg,
                             const char* file,
                             size_t line)
    {
        char buff[256];
        snprintf(buff,
                 256,
                 "ERROR [%s(%lu)]: %s",
                 file,
                 line,
                 errMsg.c_str());
        
        return std::string(buff);
    }

    bool createMakefileFromTemplate(std::istream& mkTemplate,
                                    std::ostream& destMakefile,
                                    const std::string& mkTargetName)
    {
	return CastUtil::createResult;
    }

    std::string getCastDir()
    {
	return CastUtil::castDir;
    }
    
}

#endif //CASTUTIL_H
