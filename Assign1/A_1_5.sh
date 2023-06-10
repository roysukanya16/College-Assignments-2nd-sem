#!/bin/bash

while [ -z "$op" ]
do
	echo "Enter the username: "
	read user
	op=`grep -w $user ../../../../../etc/passwd`
	echo "WRONG INPUT"
	
	
done


echo -n "Field 1 => Username:  "
grep $user /etc/passwd |cut -d ":" -f1

echo -n "Field 2 => Password:  "
grep $user /etc/passwd |cut -d ":" -f2

echo -n "Field 3 => User id:  "
grep $user /etc/passwd |cut -d ":" -f3

echo -n "Field 4 => Group id:  "
grep $user /etc/passwd |cut -d ":" -f4

echo -n "Field 5 => User id info:  "
grep $user /etc/passwd |cut -d ":" -f5

echo -n "Field 6 => Home Directory:  "
grep $user /etc/passwd |cut -d ":" -f6

echo -n "Field 7 => Login Shell:  "
grep $user /etc/passwd |cut -d ":" -f7


