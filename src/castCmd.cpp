// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include "castCmd.h"

#include "castUtil.h"
#include "cmdLine.h"
#include "trace.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>

#include <unistd.h>

extern int usage();

namespace cas
{
  std::auto_ptr<CastCmd> createCommand(const CmdLine& cmdLine);

    CastCmd::Error::Error(const std::string& err,
			  const char* file,
			  size_t line)
        : std::runtime_error(createErrMsg(err, file, line))
    {}

    bool CastCmd::executeCmd(const cas::CmdLine& cmdLine)
    {
        std::auto_ptr<CastCmd> cmd(createCommand(cmdLine));
	
	if(!cmd.get())
	    return false;

	return cmd->exec();
    }
  
    CastCmd::CastCmd(const CmdLine& cmdLine)
      : name_()
    {
        if(!cmdLine.args.empty())
	    name_ = cmdLine.args[0];
    }

    CastCmd::~CastCmd()
    {}

    bool CastCmd::exec()
    {
        cas_print("casTest: UNRECOGNIZED command: " << name_);
	usage();
	return true;
    }

    struct AddTestSuiteCmd : CastCmd
    {
        AddTestSuiteCmd(const CmdLine& cmdLine)
	  : CastCmd(cmdLine),
	    testName_(),
	    makefileName_()
        {
	    if(2 > cmdLine.args.size())
	        throw xCastCmd("Too few args for -addTestSuite command");

	    testName_ = cmdLine.args[1];
	    makefileName_ = testName_;
	    makefileName_ += ".mak";
	}

        void createMainMakefileIfNecessary()
        {
	  if(0 == access("Makefile", F_OK))
	    return;

	  std::ofstream mkfile("Makefile");
	  mkfile << "%:" << std::endl;
	}

        bool populateMainMakefile(const std::string& makefileName_)
        {
	    createMainMakefileIfNecessary();

	    bool lineFound(false);
	    std::string mkfileLine("\t$(MAKE) -f ");
	    mkfileLine += makefileName_;
	    mkfileLine += " $@";
	    
	    std::ofstream tmp("Makefile.tmp");
	    std::ifstream ori("Makefile");
	    std::string buffer;
	    
	    while(std::getline(ori, buffer))
	    {
		if(0 == buffer.compare(mkfileLine))
		    lineFound = true;

		tmp << buffer << '\n';
	    }

	    if(!lineFound)
	        tmp << mkfileLine << std::endl;

	    remove("Makefile");
	    rename("Makefile.tmp", "Makefile");
	  
	    return true;
	}

        bool createMakeFile(const std::string& castDir)
        { 
	    std::string mkTemplate(castDir);
	    mkTemplate += "/rules.make/testTemplate.mak";
	  
	    if(!createMakefileFromTemplate(mkTemplate,
					   makefileName_,
					   testName_))
	        return false;

	    return populateMainMakefile(makefileName_);
	}

        bool createSource()
        {
	    std::string srcName(testName_);
	    srcName += ".tpp";

	    std::ofstream src(srcName.c_str());

	    src << "#include \"testCase.h\"\n\n"
		<< "DEFINE_TEST(SanityTest)\n"
		<< "void run()\n"
		<< "{\n"
		<< "    bool val(false);\n\n"
		<< "    CK(true == val);\n"
		<< "}\n"
		<< "END_DEF\n\n"
		<< std::endl;

	    return true;
	}

        bool exec()
        {
	    const char* castDir(getenv("CAST_DIR"));

	    if(!castDir)
	        throw xCastCmd("$CAST_DIR not defined");

	    if(!createMakeFile(castDir))
	        throw xCastCmd("Couldn't copy makefile template");

	    createSource();

	    return true;
        }

      private:
          std::string testName_;
          std::string makefileName_;
    };

    struct AboutCmd : CastCmd
    {
        AboutCmd(const CmdLine& cmdLine)
	    : CastCmd(cmdLine)
        {}

        bool exec()
        {
            std::cout
	        << "\nThank you for trying casTest.  casTest is meant to be "
		<< "a clean and simple unit test framework.  "
		<< "I hope you find it so....Randy"
		<< "\n\n(C) 2015, 2017 Randall Lee White\n"
		<< std::endl;

	    return true;
	}
    };

    std::auto_ptr<CastCmd> createCommand(const CmdLine& cmdLine)
    {
        if('-' != cmdLine.args[0][0])
	  return std::auto_ptr<CastCmd>();

	CastCmd* cmd(0);

	if(0 == cmdLine.args[0].compare("-addTestSuite"))
	{
	    cmd = new AddTestSuiteCmd(cmdLine);
	}
	else if(0 == cmdLine.args[0].compare("-about"))
	{
	    cmd = new AboutCmd(cmdLine);
	}
	else
	{
	  cmd = new CastCmd(cmdLine);
	}

	return std::auto_ptr<CastCmd>(cmd);
    }
}
