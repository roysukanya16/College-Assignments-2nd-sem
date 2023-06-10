#!/bin/bash

ch=1
while true
do

echo "Enter Assignment number: "
echo "1. Assign1 "
echo "2. Assign2 "
echo "3. Assign3 "
echo "4. Assign4 "
read FUT
h=0
if [ $FUT -gt 0 ]
then
	if [ $FUT -lt 5 ]
	then
	case "$FUT" in
 	  1) echo "Now you are in Assignment 1 " 	
		cd ./Assign1
		echo " Question no 1 "
		echo " Question no 2 "
		echo " Question no 3 "
		echo " Question no 4 "
		echo " Question no 5 "
		read num;
		if [ $num -lt 6 ]
		then
			case "$num" in
				1) echo "question 1"
					bash A_1_1.sh
				;;
				2) echo "question 2"
					bash A_1_2.sh 
				;;
				3) echo "question 3"
					bash A_1_3.sh
				;;
				4) echo "question 4"
					bash A_1_4.sh
				;;
				5) echo "question 5"
				    bash A_1_5.sh
				;;
			esac
			cd ..
		else
			echo "invalid input"
		fi
 		
	   ;;
 	  2) echo "Now you are in Assignment 2 " 	
		cd ./Assign2
		echo " Question no 1 "
		echo " Question no 2 "
		echo " Question no 3 "
		echo " Question no 4 "
		echo " Question no 5 "
		read num;
		if [ $num -lt 6 ]
		then
			case "$num" in
				1) echo "question 1"
					sh A_2_1.sh
				;;
				2) echo "question 2"
					sh A_2_2.sh
				;;
				3) echo "question 3"
					sh A_2_3.sh
				;;
				4) echo "question 4"
					sh A_2_4.sh
				;;
				5) echo "question 5"
					sh A_2_5.sh
				;;
				
			esac
			cd ..

		else
			echo "invalid input"
		fi
 		
	   ;;
	   3)
			cd ./Assign3
		echo " Question no 1 "
		echo " Question no 2 "
		echo " Question no 3 "
		echo " Question no 4 "
		echo " Question no 5 "
		echo " Question no 6 "
		read num;
		if [ $num -lt 7 ]
		then
			case "$num" in
				1) echo "question 1"
					bash A_3_1.sh<A_3_1.in>A_3_1.op
					cat A_3_1.op
				;;
				2) echo "question 2"
					bash A_3_2.sh
				;;
				3) echo "question 3"
					bash A_3_3.sh
				;;
				4) echo "question 4"
					bash A_3_4.sh
				;;
				5) echo "question 5"
				cd 
				    cd ./Assign3
				    sh A_3_5.sh
				    cd ..
				;;
				6) echo "question 6"
				    sh Assign6.sh
				;;
			esac
			cd ..

		else
			echo "invalid input"
		fi 
	   ;;
	   *) echo "wrong choice"
	esac



	else
		echo "wrong choice"
	fi
else
	echo "wrong choice "
fi



echo "Enter 0 to exit"
read ch
if [ $ch -eq 0 ]
then 
	break
fi

done
