#ifndef CASUNISTD_H
#define CASUNISTD_H

std::string& mockCastDir()
{
    static std::string cdir("myCastDir");
    
    return cdir;
}
    
namespace cas
{
    const char* getEnv(const char* key)
    {
        std::string& cdir(mockCastDir());

        if("" == cdir)
            return 0;

        return cdir.c_str();
    }

}

#endif //CASUNISTD_H
