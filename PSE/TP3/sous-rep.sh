#!/bin/sh

if [ $# -lt 1 ]
then
	echo "Il faut 1 argument minimum"
	exit 1
else
	for i in $*
	do
	if [ ! -d $i ]
	then
		echo "L'argument $i doit être un répertoire"
		exit 1
	else
		if [ ! -r $i ]
		then
			echo " Vous n'avez pas les droits de lecture de $i"
		else
			ls -Ad $i/*/
		fi
	fi
	done
fi
exit 0
