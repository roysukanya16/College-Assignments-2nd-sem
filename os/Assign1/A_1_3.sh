#!/bin/bash
echo -n "Enter a five digit number: "
read num
echo $num
sum=0
while [ $num -ne 0 ]
do
	rem=`expr $num % 10`
	sum=`expr $sum + $rem`
	num=`expr $num / 10`
done
echo "Sum: $sum"
