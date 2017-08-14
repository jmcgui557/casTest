// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#ifndef DYNLIBUTIL_H
#define DYNLIBUTIL_H

namespace cas
{
    struct DynLibUtil
    {
        static const int LD_LAZY;
        static const int LD_NOW;
        static const int LD_BINDING_MASK;
        static const int LD_NOLOAD;
        static const int LD_DEEPBIND;
        static const int LD_GLOBAL;
        static const int LD_LOCAL;
        static const int LD_NODELETE;

        static int close(void* handle);
        static const char* error();
        static void* open(const char* filename, int flags);
        static void* sym(void* handle, const char* symbol);
        
    private:
        //no objects
        ~DynLibUtil();
    };
}

#endif //DYNLIBUTIL_H
