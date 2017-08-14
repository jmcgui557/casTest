#include "casUniStd.h"

#include <cstdlib>

namespace cas
{
    const char* getEnv(const char* key)
    {
	return getenv(key);
    }
}
