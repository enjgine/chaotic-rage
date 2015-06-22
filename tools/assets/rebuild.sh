#!/bin/bash
#
# Finds all .blend files in the orig/ directory, and convert them
# to .dae format, saving the resulting files in the correct directory
#
set -e

# Drop into repository root
cd `dirname $0`
cd ../..

# For the coloured status fields
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)

# Take first argument as a filter on model name, if specified
if [ "$1" != "" ]; then
	MATCH="$1*.blend"
else
	MATCH="*.blend"
fi

# Find files in the source directory, and process into the destination directory
function process {
	for FILE in $(find $1 -name "$MATCH"); do
		echo -n "$FILE "

		ERROR=$((
			blender -b "$FILE" -P tools/assets/rebuild_blender.py -- "$2" >/dev/null
		) 2>&1)

		if [ "$ERROR" == "" ]; then
			echo " $GREEN[ OK ]$NORMAL"
		else
			echo " $RED[FAIL]$NORMAL"
			echo
			echo "$ERROR"
			echo
		fi
	done
}

# Do the processing
process "orig/doodads" "data/cr/models"
process "orig/misc" "data/cr/models"
process "orig/units" "data/cr/models"
process "orig/vehicles" "data/cr/models"
process "orig/weapons" "data/cr/models"
