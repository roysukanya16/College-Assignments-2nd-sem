#!/bin/bash
echo -n "Enter The salary: "
read basic
echo $basic
da=`expr $basic \* 50 / 100`
hra=`expr $basic \* 20 / 100`
echo "DA: $da"
echo "HRA: $hra"
sal=`expr $da + $hra`
echo "Net Salary: $sal"


