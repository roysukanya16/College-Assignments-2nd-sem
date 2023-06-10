IFS=":"
for i in $PATH
do
	echo "Directory: $i"
	
	echo -n "Information: "
	echo `ls -ld $i | awk -F ' ' '{print $1}'`
	
	echo -n "Modification time: "
	echo `ls -ld $i | awk -F ' ' '{print $6,$7,$8}'`
done
