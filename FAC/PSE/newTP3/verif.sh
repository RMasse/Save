#!/bin/sh

if [ $# != 2 ]
then
	echo "Il faut 2 arguments"
else
	if [ ! -f $1 ]
	then
		echo "Le 1e argument doit être un fichier"
	elif [ ! -d $2 ]
	then
		echo "Le 2e argument doit être un répertoire"
	else
		echo "Tout va bien"
	fi
fi
