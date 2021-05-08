#!/bin/bash

echo -e "Executing: ${0}" # print filename
set -e # exit on any failure (e.g. a crashing test)
set -o pipefail # propagate a failure through pipe

# #############################################################################################################
# variables

DIR_CURRENT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"


# #############################################################################################################
# functions

function commands
{
	echo "Following commands exist:"
	echo "- help"
	echo "- emsdk"
}


# #############################################################################################################
# run

if [ -z ${1} ] || [ ${1} == "help" ] ; then
	commands
elif [ ${1} == "emsdk" ] ; then
	cd /deploy
	/qt-everywhere-src-5.15.2/qtbase/bin/qmake /source/qt_project.pro
	make
elif [ ${#} == 1 ] && [ -e ${1} ]; then
	${1}
else
	echo "Command not found"
	commands
	exit 1;
fi
