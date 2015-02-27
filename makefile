# The "Clean And Simple Test" (CAST) software framework, tools, and
# documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file "LICENSE"
# in the CAS poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
# Just download it and use it.
# 
# Copyright (c) 2015 Randall Lee White

all: testEnv
	$(MAKE) -C src $@

install: testEnv
	$(MAKE) -C src $@

distclean: testEnv
	$(MAKE) -C src veryclean
	rm -f `find . -name "*~"`
	rm -f distro/*

distro: distclean
	tools/makeDistro.bash

%: testEnv
	$(MAKE) -C src $@

.PHONY: testEnv
testEnv:
ifeq ('$(CAST_DIR)','')
	echo "CAST_DIR not defined"
endif
