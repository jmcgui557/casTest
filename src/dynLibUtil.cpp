// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#include "dynLibUtil.h"

#include <dlfcn.h>

namespace cas
{
    const int DynLibUtil::LD_LAZY(RTLD_LAZY);
    const int DynLibUtil::LD_NOW(RTLD_NOW);
    const int DynLibUtil::LD_BINDING_MASK(RTLD_BINDING_MASK);
    const int DynLibUtil::LD_NOLOAD(RTLD_NOLOAD);
    const int DynLibUtil::LD_DEEPBIND(RTLD_DEEPBIND);
    const int DynLibUtil::LD_GLOBAL(RTLD_GLOBAL);
    const int DynLibUtil::LD_LOCAL(RTLD_LOCAL);
    const int DynLibUtil::LD_NODELETE(LD_NODELETE);

    int DynLibUtil::close(void* handle)
    {
        return ::dlclose(handle);
    }

    const char* DynLibUtil::error()
    {
        return ::dlerror();
    }

    void* DynLibUtil::open(const char* filename, int flags)
    {
        return ::dlopen(filename, flags);
    }

    void* DynLibUtil::sym(void* handle, const char* symbol)
    {
        return ::dlsym(handle, symbol);
    }
}
