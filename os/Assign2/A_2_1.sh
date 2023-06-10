#!/bin/bash
dir=`ls`
for file in $dir; do
	if [ -d $file ]; then
		echo "$file is a directory"
	fi
	if [ -f $file ]; then
		echo "$file is a dregular file"
	fi
done
