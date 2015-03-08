// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include <unistd.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace cas
{
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

  void readMainMakefile(std::vector<std::string>& lines)
  {
    std::ifstream mkfile("Makefile");
    
    std::string buffer;
    while(std::getline(mkfile, buffer))
      lines.push_back(buffer);
  }

  

    bool createMakefileFromTemplate(const std::string& mkTemplate,
				    const std::string& destMakefile,
				    const std::string& mkTargetName)
    {
        std::ifstream infile(mkTemplate.c_str());
	std::ofstream outFile(destMakefile.c_str());

	std::string tgtSrc(mkTargetName);
	tgtSrc += ".tpp";

	std::string buff;
	while(std::getline(infile, buff))
	{
	    if(0 == buff.compare("TGT :="))
	    {
		buff += ' ';
		buff += mkTargetName;
		buff += ".test";
	    }

	    if(0 == buff.compare("TSTSRC :="))
	    {
		buff += ' ';
		buff += mkTargetName;
		buff += ".tpp";
	    }

	    outFile << buff << std::endl;
	}

	return true;
    }
}
