#include "version.h"

namespace cas
{
    const std::string& version()
    {
        static std::string ver("1.0");
        
        return ver;
    }
}

