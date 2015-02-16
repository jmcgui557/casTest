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
    
        //Returns true if a command was created from the passed args.
        //Calls exec() on the created command.  CastCmd objects may
        //throw CastCmd::Error on failure.
        static bool executeCmd(const CmdLine& cmdLine);

        virtual ~CastCmd();
        virtual void exec() = 0;
    };
}
    
#endif
