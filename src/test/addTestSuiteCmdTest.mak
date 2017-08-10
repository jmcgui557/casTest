##### TODO #####
# Set TGT to the single target created by this makefile.
#
# EX:
#    TGT := mytest.test
################
TGT := addTestSuiteCmdTest.test

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
TSTSRC := addTestSuiteCmdTest.tpp

##### TODO #####
# List other required sources here.
################
SRCS := ../cmdLine.cpp \
        ../castCmd.cpp \
	../castUtil.cpp \
	../version.cpp

#*****
# When the class under test is listed as
# part of $(SRCS), the directory .., seems to be
# used as an include automatically.  Since we
# are trying to include mocks/fileFactory.h
# we've just included ../addTestSuiteCmd.cpp
# in addTestSuiteCmdTest.tpp.  This may be a bit
# unconventional, but it works.
#*****

##### TODO #####
# If your target requires additional
# include paths, list them here.
#
# EX:
#    -I<projectIncludePath>
################
INCLUDES := -Imocks \
	    -I.. \

################
# The default values for INCLUDES, CFLAGS, LFLAGS, LPATHS, LIBS,
# and TDEPS will probably suffice for most tests.  However, if your
# test requires special include paths, compile/link flags, library
# paths, and/or libs, just include them below.
################

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
