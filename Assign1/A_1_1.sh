#!/bin/bash

echo  -n "Enter length:  "
read l
echo $l
echo  -n "Enter breadth:  "
read b
echo $b
echo -n "Area "
echo `expr $l \* $b`
echo -n "Perimeter "
echo `expr 2 \* \( $l + $b \)`
