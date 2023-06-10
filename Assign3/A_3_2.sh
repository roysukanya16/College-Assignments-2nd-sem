#!/bin/bash

fc=`ls -l | awk '{print $1}' | grep -w "-" | wc -l`
dc=`ls -1d */ | wc -l`

echo "Number of files: $fc"
echo "Number of directories: $dc"

echo "Files:"
ls -l | awk '{print $1,$9}' | grep -w "-" | awk '{print $2}'

echo "Directories:"
ls -1d */ 