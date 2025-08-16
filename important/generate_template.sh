#!/bin/sh

#filename
filename=$1
#file extension
extension="${filename##*.}"

if [ "$extension" == "cpp" ]; then
	cp -n ~/templates/competitive/template.cpp ./$filename
	chmod 777 ./$filename
	touch $filename.test
else
	echo "Error"
	echo "Template not found"
	echo "or file extension not valid"
	exit
fi

vim $filename -c 28
