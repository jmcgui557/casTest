#! /bin/bash

createBashScript()
{
    local scriptName="$castDir/castEnv.sourceMe.bash"

    if [ ! -e "$scriptName" ]; then
	touch $scriptName

	cat $castDir/COPYRIGHT >> $scriptName
	echo "export CAST_DIR=$castDir" >> $scriptName
	echo ". \$CAST_DIR/cast_env.bash" >> $scriptName
	echo "" >> $scriptName

	ln -s $scriptName $HOME
    fi
}

createCshScript()
{
    local scriptName="$castDir/castEnv.sourceMe.csh"

    if [ ! -e "$scriptName" ]; then
	touch $scriptName

	cat $castDir/COPYRIGHT >> $scriptName
	echo "setenv CAST_DIR $castDir" >> $scriptName
	echo ". \$CAST_DIR/cast_env.csh" >> $scriptName
	echo "" >> $scriptName

	ln -s $scriptName $HOME
    fi
}

createEnvironmentScripts()
{
	createBashScript
	createCshScript
}

if [ 0 == $# ]; then
    echo "USAGE:"
    echo "    genShellScripts.bash <CAST_DIR>"
    exit 1
fi

castDir=$1
oldDir=`pwd`

cd $castDir

createEnvironmentScripts

cd $oldDir
