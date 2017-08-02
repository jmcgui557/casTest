# The "Clean And Simple Test" (CAST) software framework, tools, and
# documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file "LICENSE"
# in the CAS poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
# Just download it and use it.
# 
# Copyright (c) 2015 Randall Lee White

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkdir := $(dir $(mkfile_path))
envScript := $(mkdir)castEnv.sourceMe.bash
envScriptLink := $(HOME)/castEnv.sourceMe.bash

all: autoSourceBuild
	$(MAKE) -C tools/src $@
	$(MAKE) -C src $@

install: autoSourceBuild
	$(MAKE) -C tools/src $@
	$(MAKE) -C src $@
	$(MAKE) -C tools/src/test $@

distclean: autoSourceBuild
	$(MAKE) -C tools/src veryclean
	$(MAKE) -C src veryclean
	rm -f `find . -name "*~"`
	rm -f distro/*

distro: distclean
	tools/makeDistro.bash

%: autoSourceBuild
	$(MAKE) -C tools/src $@
	$(MAKE) -C src $@

.PHONY: autoSourceBuild
autoSourceBuild:
ifeq ('$(CAST_DIR)','')
	echo "Auto sourcing: $(envScript)"
	$(mkdir)/tools/genShellScripts.bash $(mkdir); \
	. $(envScript); cd $(mkdir); \
	$(MAKE) $(MAKECMDGOALS)
	@echo ""
	@echo "WARNING: For more efficient builds/makes, please source:"
	@echo "             '$(envScript)'"
	@echo "                  or"
	@echo "             '$(envScriptLink)'"
	@echo "         (or their t/csh equivalents) before making any "
	@echo "         casTest target."
	@echo ""
	@echo "         Please disregard the 'StOp' and 'autoSourceBuild'"
	@echo "         errors following this warning.  We're just forcing"
	@echo "         an error to exit make."
	@StOp
endif
