#!/bin/bash

for file in `ls *~`
do
	echo "Deleted file: $file"
	rm $file
done 
