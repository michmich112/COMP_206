#!/bin/bash

# kill all the instances of eog
#killall eog

tes=`ls | cut -d' ' -f1`
echo "the name of the file is `$tes | cut -d' ' -f1`"

#get the names of the images in an array
declare -a pics=("blue_whale.jpg" "crocodile.jpg" "elephant.jpg" "giraffe.jpg" "hippopotamus.jpg" "humpback_whale.jpg" "ostrich.jpg" "sea_turtle.jpg")

for i in "${pics[@]}"
do
		echo "$i"
done



