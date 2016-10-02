#!/bin/bash

#
#Author:	Michel Cantacuzene
#Version:	0.1
#Name:		q2.bash
#Description:	Provides optimal time waste by displaying N images (N being a paramater) at a time to the user and cycling endlessly.
#

#define the numebr of images to be opened:
NUM=$1

#define the files we can use
FILES="blue_whale.jpg crocodile.jpg elephant.jpg giraffe.jpg hippopotamus.jpg humpback_whale.jpg ostrich.jpg sea_turtle.jpg"

#we kill all the preveously opened eog instances (instances that were opened by the program)
#We first verify if there are eog processes open
PROC=`ps | grep eog`
if [ -n "$PROC" ]
then
	killall eog
fi

#function to open a new instance of eog with a different animal
function openNew()
{
	NAME=`echo $FILES | cut -d' ' -f1`
	FILES="`echo $FILES | cut -d' ' -f2-` ${NAME}"
	eog "$NAME" -n & #correct for accessing in the jpgs directory
	INSTANCES=`ps | grep eog | wc -l`
}	

#initial operation
function initiate()
{
	if [ -z `ps | grep eog` ] 
	then
		INSTANCES=`ps | grep eog | wc -l`
		if [ $INSTANCES -lt  $NUM ]
		then
			while [ $INSTANCES -lt  $NUM ]
			do
				openNew
			done
		fi
	fi
}

#main function
function main()
{
	while [ 1 ]
	do
		INSTANCES=`ps | grep eog | wc -l`
		if [ $INSTANCES -lt $NUM ]
		then
			openNew
		fi
	done
}

#program
initiate
main
