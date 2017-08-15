// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAST poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
//
// Copyright (c) 2017 Randall Lee White

#include "casStdLib.h"

#include <cstdlib>

namespace cas
{
    const char* getEnv(const char* key)
    {
        return getenv(key);
    }
}
