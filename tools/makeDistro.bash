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

tarBall=cast.tgz

tarFiles()
{
    local files=`ls -1 | grep -v distro` #all files and directories in cwd

    tar -czf distro/$tarBall $files
}

buildInstallScript()
{
    rm -rf distro/*
    cp tools/selfExtract.bash distro
    tarFiles

    cd distro
    cat selfExtract.bash $tarBall > installCast.bin

    chmod 775 installCast.bin
    rm -f selfExtract.bash $tarBall
    cd -
}

main()
{
    if [ "" == $CAST_DIR ]; then
	echo "CAST_DIR is not defined."
	exit 1
    fi

    local OLDDIR=`pwd`

    cd $CAST_DIR

    buildInstallScript

    cd $OLDDIR
}

main "$@"
