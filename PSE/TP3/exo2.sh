#!/bin/sh

if [ $# != 2 ]
then
	echo "Il faut 2 arguments" >&2
	exit 1
else
	if [ ! -f $1 ]
	then
		echo "Le 1e argument doit être un fichier" >&2
		exit 1
	elif [ ! -d $2 ]
	then
		echo "Le 2e argument doit être un répertoire" >&2
		exit 1
	else
		echo "Tout va bien"
	fi
fi
exit 0
