#ifndef CASUNISTD_H
#define CASUNISTD_H

namespace cas
{
    const char* getEnv(const char* key)
    {
	static const char* cdir("myCastDir");

	return cdir;
    }

}

#endif //CASUNISTD_H
