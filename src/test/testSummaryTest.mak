# The "Clean And Simple" (CAS) software framework, tools, and documentation
# are distributed under the terms of the MIT license a copy of which is
# included with this package (see the file "LICENSE" in the CAS poject tree's
# root directory).  CAST may be used for any purpose, including commercial
# purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like
# "copyleft" restrictions, either.  Just download it and use it.
# 
# Copyright (c) 2015, 2017 Randall Lee White

##### TODO #####
# Set TGT to the single target created by this makefile.
#
# EX:
#    TGT := mytest.test
################
TGT := testSummaryTest.test

INSTALL_DIR := $(CAST_DIR)/test

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
# NOTE: Due to the way test sources are processed,
#       only one test source may be listed.
################
TSTSRC := testSummaryTest.tpp

##### TODO #####
# List other required sources here.
################
SRCS := ../testSummary.cpp

################
# The default values for INCLUDES, CFLAGS, LFLAGS, LPATHS, LIBS,
# and TDEPS will probably suffice for most tests.  However, if your
# test requires special include paths, compile/link flags, library
# paths, and/or libs, just include them below.
################

##### TODO #####
# If your target requires additional
# include paths, list them here.
#
# EX:
#    -I<projectIncludePath>
################
INCLUDES := -I..

##### TODO #####
# If your target requires special
# compile flags, list them here.
#
# EX:
#    -fno-default-inline
################
CFLAGS :=

##### TODO #####
# If your target requires special
# link flags, list them here.
#
# EX:
#    -Wl,--no-as-needed
################
LFLAGS :=

##### TODO #####
# Paths to libraries.
#
# EX:
#     -L<pathToProjectLib>
################
LPATHS :=

##### TODO #####
# If your target must be linked to
# additional libraries, list them here.
#
# EX:
#     -lrt
################
LIBS :=

##### TODO #####
# If your target has addition target
# dependencies, list them here.
################
TDEPS :=

include $(CAST_DIR)/rules.make/makefile.test
