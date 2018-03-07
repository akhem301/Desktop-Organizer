#!/bin/bash

g++ deskorg.cpp
./a.out

location=("Videos" "Photos" "Docs" "Zip" "Music")
ind=-1
filename="$HOME/Documents/fileinfo.txt"
while read -r line
do
    name="$line"
    len=${#name}
    
    #echo "$ind"
    if [ $len -eq 1 ]
    then 
		((ind++))
		if [ ! -d "$HOME"/Documents/"${location[ind]}" ]; 
		then
			mkdir "$HOME"/Documents/"${location[ind]}"
		fi
		
	else
		mv "$HOME"/Desktop/"$name" "$HOME"/Documents/"${location[ind]}"
	fi
	
done < "$filename"

rm "$filename"
