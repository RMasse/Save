#!/bin/sh


if [ $(($#%2)) != 0 ] || [ $# -eq 0 ]
then
	echo "Il faut un nombre pair d'arguments" >&2
	exit 1
else
	for i in $*
	do
		if [ $(($#%2)) != 0 ]
		then
			shift
		else
			cp $1 $2
			echo " $1 a été copié dans $2"
			shift
		fi
	done
fi
exit 0
