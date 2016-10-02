#!/bin/bash

#
#Author:	Michel Cantacuzene
#Version:	0.1
#Name:		q3.bash
#Description:	Sorts the given animals using 3 categories: Name, Wheight, Length.
#


ANIMALS="blue_whale crocodile elephant giraffe hippopotamus humpback_whale ostrich sea_turtle"

function picmake() #function that creates the result.jpg image
{
	#first parameter is the filename
	filename=$1
	animal=`head -n 1 $filename | tail -n 1`
	file="jpgs/"$animal".jpg"
	cp $file result.jpg
	for i in 2 3 4 5 6 7 8
	do
		animal=`head -n $i $filename | tail -n 1`
		file="jpgs/"$animal".jpg"
		convert result.jpg $file -append result.jpg
	done
	eog -n result.jpg &
}

function namesort() #function that sorts the animals alphabeticaly
{
	FILES=$ANIMALS
	for i in 1 2 3 4 5 6 7 8
	do
		NAME=`echo $FILES | cut -d' ' -f1`
		FILES="`echo $FILES | cut -d' ' -f2-`"
		echo $NAME >> names.txt
	done
	sort names.txt > /dev/null
	cat names.txt
}

function wheightsort() #function that sorts the animals by wheight
{
	FILES=$ANIMALS
	for i in 1 2 3 4 5 6 7 8
	do
		NAME=`echo $FILES | cut -d' ' -f1`
		FILES="`echo $FILES | cut -d' ' -f2-`"
		VAL=`cat "./data/"$NAME".dat" | cut -d' ' -f1`
		echo "$VAL $NAME " >> tmp.txt
	done
	cat tmp.txt | sort -n | cut -d' ' -f2 > wheight.txt
	rm -f tmp.txt
	cat wheight.txt
}

function lengthsort() #function that sorts the animals by length
{
	FILES=$ANIMALS
	for i in 1 2 3 4 5 6 7 8
	do
		NAME=`echo $FILES | cut -d' ' -f1`
		FILES="`echo $FILES | cut -d' ' -f2-`"
		VAL=`cat "./data/"$NAME".dat" | cut -d' ' -f2`
		echo "$VAL $NAME " >> tmp.txt
	done
	cat tmp.txt | sort -n | cut -d' ' -f2 > length.txt
	rm -f tmp.txt
	cat length.txt
}

function main() #main function
{
	case "$1" in
		alpha)
			namesort
			picmake names.txt
			rm -f names.txt
			;;
		wheight)
			wheightsort
			picmake wheight.txt
			rm -f wheight.txt
			;;
		length)
			lengthsort
			picmake length.txt
			rm -f length.txt
			;;
		*)
			echo -e "Insert one of the following parameters:\n	alpha (for alphabetical sorting);\n	wheight (for wheight sorting);\n	length (for length sorting)."
	esac
}

main $1 #run the program
