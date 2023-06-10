#!/bin/bash

while read line
do	
	echo -n " $line"
	IFS=" "
	sum=0
	for l in $line
	do
		sum=`expr $sum + $l`
	done
	echo "   sum: $sum"
done
