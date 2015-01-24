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

validateInput()
{
    local EXT=`echo "$1" | cut -d"." -f2`
    
    if [ "tpp" != "$EXT" ]; then
	echo "Invalid file type: $EXT"
	exit 1
    fi
}

collectTests()
{
    local SRC=$1
    local TEST
    local TESTS
    local TMP
    
    while read line
    do
	TMP=`echo $line | grep DEFINE_TEST`
	
	if [ "" != "$TMP" ]; then 
	    TEST=`echo "$line" | cut -d"(" -f2`
	    TEST=`echo "$TEST" | cut -d")" -f1`
	    TEST=`echo "$TEST" | cut -d"," -f1`
	    TESTS="$TESTS $TEST"
	fi
    done < $SRC

    echo "$TESTS"
}

copySrcToTgt()
{
    local SRC=$1
    local TGT=$2

    if [ -f $SRC ]; then
	rm -f $TGT
	cat $SRC > $TGT
    else
	echo "Error: Source $SRC not found"
	exit 1
    fi
}

appendIncludes()
{
    local TGT=$1
    
    echo "" >> $TGT
    echo "//------------------------------------------" >> $TGT

    grep "#include" $TGT | grep "vector" > /dev/null

    if [ 0 != $? ]; then
	echo "#include <vector>" >> $TGT
    fi
}

appendTests()
{
    local TEST_LINES=$1
    local TGT=$2

    echo "" >> $TGT
    echo "extern \"C\"" >> $TGT

    echo "{" >> $TGT
    echo "    void createTests(std::vector<cas::TestCase*>& tests)" >> $TGT
    echo "    {" >> $TGT

    local TEST
    
    for line in $TEST_LINES
    do
	TEST=`echo "$line" | cut -d"(" -f2`
	TEST=`echo "$TEST" | cut -d")" -f1`
	TEST=`echo "$TEST" | cut -d"," -f1`
	echo "        tests.push_back(new $TEST);" >> $TGT
    done

    echo "    }" >> $TGT
    echo "}" >> $TGT
    echo "" >> $TGT
    echo "" >> $TGT
}

main()
{
    SRC=$1

    validateInput $SRC
    
    TGT=`basename $SRC .tpp`.cpp
    
    echo "$(basename $0): $SRC -> $TGT"

    TESTS=$(collectTests $SRC)
    
    if [ "" == "$TESTS" ]; then
	echo "Error: No tests found"
	exit 1
    fi

    copySrcToTgt $SRC $TGT
    
    appendIncludes $TGT
    appendTests "$TESTS" $TGT
    
    echo "Done"
}

main $@
