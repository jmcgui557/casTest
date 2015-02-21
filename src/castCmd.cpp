#include "castCmd.h"

#include "castUtil.h"
#include "cmdLine.h"
#include "trace.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>

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

    struct InitTestCmd : CastCmd
    {
        InitTestCmd(const CmdLine& cmdLine)
	  : CastCmd(cmdLine),
	    testName_(),
	    makefileName_("Makefile")
        {
	    if(2 > cmdLine.args.size())
	        throw xCastCmd("Too few args for -initTest command");

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
		<< "    Assert(val,\n"
		<< "           \"Please change val to true, "
		<< " and try again.\");\n"
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
		<< "\n\n(C) 2015 Randall Lee White\n"
		<< std::endl;

	    return true;
	}
    };

    std::auto_ptr<CastCmd> createCommand(const CmdLine& cmdLine)
    {
        if('-' != cmdLine.args[0][0])
	  return std::auto_ptr<CastCmd>();

	CastCmd* cmd(0);

	if(0 == cmdLine.args[0].compare("-initTest"))
	{
	    cmd = new InitTestCmd(cmdLine);
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
