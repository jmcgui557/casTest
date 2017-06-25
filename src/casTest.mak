# The "Clean And Simple Test" (CAST) software framework, tools, and
# documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file "LICENSE"
# in the CAS poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
# Just download it and use it.
# 
# Copyright (c) 2015 Randall Lee White

TGT := casTest

SRCS := \
	casTest.cpp \
	castCmd.cpp \
	castUtil.cpp \
	cmdLine.cpp \
	runTests.cpp \
	testLib.cpp \
	usage.cpp

GENFILES := *.gcov

UNAME_S := $(shell uname -s)

LIBS := -ldl
LFLAGS := -Wl,-R -Wl,.

ifeq ($(UNAME_S),Darwin)
    LFLAGS := -Wl,-L -Wl,.
endif

CFLAGS := -g -Wall
PFLAGS := -ftest-coverage -fprofile-arcs

##include $(CAST_DIR)/rules.make/makefile.exec##
include $(CAST_DIR)/rules.make/makefile.exec

