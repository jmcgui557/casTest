# The "Clean And Simple Test" (CAST) software framework, tools, and
# documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file "LICENSE"
# in the CAS poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
# Just download it and use it.
# 
# Copyright (c) 2015 Randall Lee White

all:
	$(MAKE) -f libcasTest.mak $@
	$(MAKE) -f casTest.mak $@
	$(MAKE) -C test $@

build: clean
	$(MAKE) -f libcasTest.mak install
	$(MAKE) -f casTest.mak install
	$(MAKE) -C test test

%:
	$(MAKE) -f libcasTest.mak $@
	$(MAKE) -f casTest.mak $@
	$(MAKE) -C test $@
