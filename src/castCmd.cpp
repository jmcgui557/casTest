#include "castCmd.h"

#include "castUtil.h"
#include "cmdLine.h"

#include "trace.h"

#include <cstdlib>

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
	    if(3 > cmdLine.args.size())
	        throw xCastCmd("Too few args for CreateNewTestCmd");

	    testName_ = cmdLine.args[2];

	    if(4 <= cmdLine.args.size())
	      makefileName_ = cmdLine.args[3];
	}

        bool doCmd(const std::string& cmd)
        {
	    int err(system(cmd.c_str()));
	    int stat(WEXITSTATUS(err));

	    return 0 == stat;
	}

        bool copyMakeFile(const std::string& castDir)
        {
	    std::string copyMakeFile("cp ");
	    copyMakeFile += castDir; 
	    copyMakeFile += "/rules.make/testTemplate.mak ";
	    copyMakeFile += makefileName_;
	    cas_print("copyMakeFile: " << copyMakeFile);
	    
	    return doCmd(copyMakeFile);
	}

        bool insertTarget()
        {
	    std::string sedCmd("sed -i 's/^TGT[[:space:]]:=.*/TGT := ");
	    sedCmd += testName_;
	    sedCmd += "/g' ";
	  
	    sedCmd += makefileName_;
	    
	    cas_print("sedCmd: " << sedCmd);
	    
	    return doCmd(sedCmd);
	}

        bool insertTestSource()
        {
	    std::string sedCmd(
                "sed -i 's/^TSTSRC[[:space:]]:=.*/TSTSRC := ");

	    sedCmd += testName_;
	    sedCmd += ".tpp";
	    sedCmd += "/g' ";
	  
	    sedCmd += makefileName_;
	    
	    cas_print("sedCmd: " << sedCmd);

	    return doCmd(sedCmd);
	}

        void exec()
        {
	    const char* castDir(getenv("CAST_DIR"));

	    if(!castDir)
	        throw xCastCmd("Couldn't $CAST_DIR not defined");

	    if(!copyMakeFile(castDir))
	        throw xCastCmd("Couldn't copy makefile template");

	    if(!insertTarget())
	        throw xCastCmd("Couldn't insert target");

	    if(!insertTestSource())
	        throw xCastCmd("Couldn't insert test source");
        }

      private:
          std::string testName_;
          std::string makefileName_;
  };
      
    CastCmd* createCommand(const CmdLine& cmdLine)
    {
        if('-' != cmdLine.args[1][0])
	    return 0;

	CastCmd* cmd(0);

	if(0 == cmdLine.args[1].compare("-newTest"))
	{
	    cmd = new CreateNewTestCmd(cmdLine);
	}

	return cmd;
    }
}
