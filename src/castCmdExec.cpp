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

#include "addTestSuiteCmd.h"
#include "castCmd.h"
#include "verCmd.h"
#include "usage.h"

#include <iostream>
#include <memory>

namespace cas
{
    struct UsageCmd : CastCmd
    {
        UsageCmd(const CmdLine& cmdLine,
                 std::ostream& out = std::cout)
            : CastCmd(cmdLine),
              out_(out)
        {}

        bool exec()
        {
            out_ << "casTest: UNRECOGNIZED command: " << name() << std::endl;
            usage();

            return true;
        }

    private:
        std::ostream& out_;
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
                << "\na clean and simple unit test framework.  "
                << "\nI hope you find it so....Randy"
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
        else if(0 == cmdLine.args[0].compare("-version"))
        {
            cmd = new VersionCmd(cmdLine);
        }
        else
        {
          cmd = new UsageCmd(cmdLine);
        }

        return std::auto_ptr<CastCmd>(cmd);
    }

    bool executeCmd(const cas::CmdLine& cmdLine)
    {
        std::auto_ptr<CastCmd> cmd(createCommand(cmdLine));
        
        if(!cmd.get())
            return false;
        
        return cmd->exec();
    }
}
  
