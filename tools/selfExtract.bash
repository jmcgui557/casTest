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

# This text file is used to generate a self-extracting gzipped tar file
# which extracts itself and accomplishes basic administrative tasks
# for installing CAS on a host.  The user may be prompted for a password 
# for certain tasks which require super user permissions.
#
# This file has been adapted from a self-extracting
# tar example by Stuart Wells.  
# See "http://stuartwells.net/slides/selfextract.htm".

castDir="$HOME/cast"
installDir=""
isRoot=0

copyrt=$"# The \"Clean And Simple Test\" (CAST) software framework, tools,
# and documentation are distributed under the terms of the MIT license a
# copy of which is included with this package (see the file \"LICENSE\"
# in the CAST poject tree's root directory).  CAST may be used for any
# purpose, including commercial purposes, at absolutely no cost. No
# paperwork, no royalties, no GNU-like \"copyleft\" restrictions, either.
# Just download it and use it.
#
# Copyright (c) 2015 Randall Lee White"

testRootUser()
{
    if [ "root" == "$USER" ]; then
	isRoot=1
    fi
}

getCastDir()
{
    local userInput=""

    if [ 1 == $isRoot ]; then
	castDir="/usr/local/cast"
    fi

    echo "Where would you like to install casT?"
    read -p "Default location: $castDir: " userInput

    if [ "" != "$userInput" ]; then
	castDir=$userInput
    fi

    echo "castDir: $castDir"
}

prepareInstallationDir()
{
    local installDir=$1
    local err=0
    local testFile="$installDir/testFile.cast"

    if [ -e $installDir ]; then
	touch $testFile

	if [ 0 != $? ]; then
            err=1
	else
	    rm $testFile
	fi
    else
        mkdir -p $installDir
	
	if [ 0 != $? ]; then
	    err=2
	fi
    fi

    return $err
}

extractFiles()
{
    local extractDir=$installDir

    echo "Extracting files to $extractDir"

    #extract the tarball
    local SKIP=`awk '/^__TARFILE_FOLLOWS__/ { print NR + 1; exit 0; }' $0`

    #remember our file name
    local THIS=`pwd`/$0

    echo "THIS: $THIS"

    # take the tarfile and pipe it into tar
    tail -n +$SKIP $THIS | tar -xz -C $extractDir

    return 0
}

createEnvironmentScript()
{
    local scriptName="$castDir/castEnv.sourceMe.bash"

    rm -f $scriptName

    touch $scriptName

    cat $castDir/COPYRIGHT >> $scriptName
    echo "export CAST_DIR=$castDir" >> $scriptName
    echo ". \$CAST_DIR/cast_env.bash" >> $scriptName
    echo "" >> $scriptName
    echo "" >> $scriptName

    echo "isRoot: $isRoot"

    if [ 1 != $isRoot ]; then
	ln -sf $scriptName $HOME/castEnv.sourceMe.bash
    fi
}

makeCast()
{
    local scriptName="$castDir/castEnv.sourceMe.bash"

    . $scriptName

    cd $CAST_DIR
    make
}

setLinksIfRoot()
{
    if [ 1 == $isRoot ]; then
	ln -sf $castDir/bin/casTest /usr/local/bin/casTest

	if [ 0 != $? ]; then
	    echo "FAILED to create link: casTest"
	fi

	ln -sf $castDir/lib/libcasTest.a /usr/local/lib/libcasTest.a

	if [ 0 != $? ]; then
	    echo "FAILED to create link: libcasTest.a"
	fi
    fi
}

main()
{
    testRootUser

    getCastDir

    installDir=$castDir.`date +%Y%m%d.%H%M.%S`

    prepareInstallationDir $installDir
    err=$?

    if [ 0 != $err ]; then
	echo "ERROR: casT installation failed."
	exit 1;
    fi

    extractFiles
    err=$?

    if [ 0 != $err ]; then
	echo "ERROR: error extracting files"
	exit 1;
    fi
    
    rm -rf $castDir
    mv $installDir $castDir
    createEnvironmentScript
    makeCast

    setLinksIfRoot
    echo "$copyrt"
}

main "$@"

exit 0

# NOTE: Don't place any newline characters after the last line below.
__TARFILE_FOLLOWS__
