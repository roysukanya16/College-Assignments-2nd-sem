#!/bin/bash
totalSize=0
for file in `ls`
do
	if [ -f "$file" ]
	then
		currFileSize=`ls -l "$file" | awk '{print $5}'`
		totalSize=`expr $totalSize + $currFileSize`
	fi
done

echo "Total size of all files: $totalSize bytes"
