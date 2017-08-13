// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2015 Randall Lee White

#include "usage.h"

#include "trace.h"

int usage(std::ostream& out)
{
    out << "\nUSAGE:"
	<< "\n\tcasTest -addTestSuite <testSuiteName>"
	<< "\n\tcasTest <testLib1> [<testLib2> <...testLibN>]"
	<< "\n"
	<< "\n\tcasTest -about"
	<< "\n\tcasTest -help"
	<< "\n\tcasTest -version" << std::endl;

    return -1;
}

