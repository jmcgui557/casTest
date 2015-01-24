# The "Clean And Simple" (CAS) software framework, tools, and documentation
# are distributed under the terms of the MIT license a copy of which is
# included with this package (see the file "LICENSE" in the CAS poject tree's
# root directory).  CAS may be used for any purpose, including commercial
# purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
# "copyleft" restrictions, either.  Just download it and use it.
# 
# Copyright (c) 2015 Randall Lee White

##### TODO #####
# Set TGT to the single target created by this makefile.
#
# EX:
#    TGT := mytest.test
################
TGT :=

##### TODO #####
# List test sources here.  Test sources are essentially C++ files which
# use the macros DEFINE_TEST (or DEFINE_TEST_FROM) and END_DEF from
# testCase.h to define the TestCase derived classes.  These files have
# a .tpp "extension" and are processed into .cpp files with the
# appropriate "createTests()" function appended.  The .cpp file is then
# compiled/linked into the test "application".  (It's really a shared
# library which is loaded from casTest.)  See the docs for more info.
#
# EX:  
#    TSTSRC := mytest.tpp
#
# NOTE: Currently, only one test source is allowed.
################
TSTSRC :=

##### TODO #####
# List required sources here.
################
SRCS := 

################
# The default values for INCLUDES, CFLAGS, LFLAGS, LPATHS, LIBS,
# and TDEPS will probably suffice for most tests.  However, if your
# test requires special include pathss, compile/link flags, library
# paths, and/or libs, just include them below.
################

INCLUDES :=

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
