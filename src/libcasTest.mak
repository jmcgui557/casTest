# The "Clean And Simple Test" (CAST) software framework, tools, and
# documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file "LICENSE"
# in the CAS poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
# Just download it and use it.
# 
# Copyright (c) 2015, 2017 Randall Lee White

TGT := libcasTest.a

SRCS := testCase.cpp
GENFILES := *.gcov

INCLUDES := -I$(CAST_INC)

#Compile flags.
CFLAGS := -fpic

#Link flags.
LFLAGS := 

#Paths to libraries.
LPATHS :=

#Libraries target is to be linked to.
LIBS :=

#Addition target dependencies.
TDEPS :=

##include $(CAST_DIR)/rules.make/makefile.staticLib##
include $(CAST_DIR)/rules.make/makefile.staticLib
