# The "Clean And Simple Test" (CAST) software framework, tools, and
# documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file "LICENSE"
# in the CAS poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
# Just download it and use it.
# 
# Copyright (c) 2015, 2017 Randall Lee White

#single target created by this makefile
TGT := selftest.test

INSTALL_DIR := $(CAST_DIR)/test
INCLUDES := -I..

#source for the target
TSTSRC := casTestSelf.tpp
GENFILES := $(TSTSRC:.tpp=.cpp) *.gcov

SRCS := \
	../castCmd.cpp \
	../castUtil.cpp \
	../cmdLine.cpp \
	../usage.cpp

#Compile flags.
CFLAGS :=

#Link flags.
LFLAGS :=

#Paths to libraries.
LPATHS :=

#Libraries target is to be linked to.
LIBS :=

#Addition target dependencies.
TDEPS :=

include $(CAST_DIR)/rules.make/makefile.test
