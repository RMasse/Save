#!/bin/sh

if [ $# -lt 1 ]
then
	echo "Il faut 1 argument minimum"
else
	for i in $*
	do
	if [ ! -d $i ]
	then
		echo "L' argument $i doit être un répertoire"
	else
		tree $i
	fi
	done
fi
