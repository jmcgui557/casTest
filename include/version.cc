#ifndef VERSION_CC
#define VERSION_CC

namespace cas
{
    const std::string& version()
    {
        static std::string ver("1.0.2");
        
        return ver;
    }
}

#endif //VERSION_CC
