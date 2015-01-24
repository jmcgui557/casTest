// The "Clean And Simple" (CAS) software framework, tools, and documentation
// are distributed under the terms of the MIT license a copy of which is
// included with this package (see the file "LICENSE" in the CAS poject tree's
// root directory).  CAS may be used for any purpose, including commercial
// purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
// "copyleft" restrictions, either.  Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#ifndef CAS_TRACE_H
#define CAS_TRACE_H

#include <iostream>
#include <string>

#define cas_print(msg) std::cout << msg << std::endl
#define cas_error(msg) std::cerr << msg << std::endl
#define cas_debug(msg) std::cerr << msg << std::endl

namespace cas
{

}

#endif //CAS_TRACE_H
