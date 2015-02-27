#! /bin/bash

# The "Clean And Simple Test" (CAST) software framework, tools, and
# documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file "LICENSE"
# in the CAST poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
# Just download it and use it.
#
# Copyright (c) 2015 Randall Lee White

TGT=$1
DST=$2

if [ "" != "$DST" ]; then
    cp $TGT $DST
fi

ENV_BASH="$CAST_DIR/tools/castEnv.sourceMe.bash"
ENV_CSH="$CAST_DIR/tools/castEnv.sourceMe.csh"

#if a link to castEnv.sourceMe.bash doesn't exist in $HOME, create it
if [ ! -e "$ENV_BASH" ]; then
    ln -s $ENV_BASH $HOME
fi

#if a link to castEnv.sourceMe.csh doesn't exist in $HOME, create it
if [ ! -e "$ENV_CSH" ]; then
    ln -s $ENV_CSH $HOME
fi

    
