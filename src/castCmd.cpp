#include "castCmd.h"

#include "castUtil.h"
#include "cmdLine.h"

#include <cstdlib>
#include <iostream>

namespace cas
{
    CastCmd* createCommand(const CmdLine& cmdLine);

    CastCmd::Error::Error(const std::string& err,
			  const char* file,
			  size_t line)
        : std::runtime_error(createErrMsg(err, file, line))
    {}

    bool CastCmd::executeCmd(const cas::CmdLine& cmdLine)
    {
        CastCmd* cmd(createCommand(cmdLine));

	if(cmd)
	{
	    cmd->exec();
	    return true;
	}

	return false;
    }
  
    CastCmd::~CastCmd()
    {}

    struct CreateNewTestCmd : CastCmd
    {
        CreateNewTestCmd(const CmdLine& cmdLine)
	  : CastCmd(),
	    testName_(),
	    makefileName_("Makefile")
        {
	    if(2 > cmdLine.args.size())
	        throw xCastCmd("Too few args for CreateNewTestCmd");

	    testName_ = cmdLine.args[1];

	    if(3 <= cmdLine.args.size())
	      makefileName_ = cmdLine.args[2];
	}

        bool createMakeFile(const std::string& castDir)
        {
	    std::string mkTemplate(castDir);
	    mkTemplate += "/rules.make/testTemplate.mak";

	    return createMakefileFromTemplate(mkTemplate,
					      makefileName_,
					      testName_);
	}

        void exec()
        {
	    const char* castDir(getenv("CAST_DIR"));

	    if(!castDir)
	        throw xCastCmd("$CAST_DIR not defined");

	    if(!createMakeFile(castDir))
	        throw xCastCmd("Couldn't copy makefile template");
        }

      private:
          std::string testName_;
          std::string makefileName_;
    };

  struct AboutCmd : CastCmd
  {
    void exec()
    {
      std::cout
	<< "\ncasTest is meant to be a clean and simple unit test framework."
	<< "\n\n(C) 2015 Randall Lee White\n"
	<< std::endl;
    }
  };
      
    CastCmd* createCommand(const CmdLine& cmdLine)
    {
        if('-' != cmdLine.args[0][0])
	    return 0;

	CastCmd* cmd(0);

	if(0 == cmdLine.args[0].compare("-newTest"))
	{
	    cmd = new CreateNewTestCmd(cmdLine);
	}
	else if(0 == cmdLine.args[0].compare("-about"))
	{
	    cmd = new AboutCmd();
	}

	return cmd;
    }
}
