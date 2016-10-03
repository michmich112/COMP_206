#!/bin/bash

list="allo top goerge"

function verify()
{
	if [ -e $1".txt" ]
	then
		return 1
	else
		return 0
	fi
}

function main()
{
	for i in 1 2 3
	do
		NAME=`echo $list | cut -d' ' -f1`
		list="`echo $list | cut -d' ' -f2-`"
		if [ `verify $NAME` ]
		then
			echo "exists"
		else
			echo "doesn't exist"
		fi
	done
}

main
