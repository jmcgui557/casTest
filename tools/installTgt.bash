#! /bin/bash

# The "Clean And Simple Test" (CAST) software framework, tools, and
# documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file "LICENSE"
# in the CAST poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
# Just download it and use it.
#
# Copyright (c) 2015, 2017 Randall Lee White

TGT=$1
DST=$2

if [ "" != "$DST" ]; then
    mkdir -p $DST
    echo "Installing $TGT to $DST"
    cp $TGT $DST
fi

    
