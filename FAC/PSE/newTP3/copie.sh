#!/bin/sh

if [ $(($#%2)) != 0 ]
then
	echo "Il faut un nombre pair d'arguments"
else
	for i in $*
	do
		if [ $(($#%2)) != 0 ]
		then
			shift
		else
			cp $1 $2
			shift
		fi
	done	
fi
