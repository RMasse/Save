#!/bin/sh

if [ $# -lt 2 ]
then
	echo "Il faut 2 arguments minimum"
	exit 1
else
	div=$1
	a=0
	shift
	for i in $*
	do
		a=$(($1%$div))
		if [ $a -eq 0 ]
		then
			echo "$1 est divisible par $div"
		fi
		shift
	done
fi
exit 0
