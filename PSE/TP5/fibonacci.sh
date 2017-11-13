#!/bin/sh

if [ $1 -eq 0 ] || [ $1 -eq 1 ] #Test si l'argument vaut 0 ou 1
then
	echo $1			#Et renvoie la valeur correspondante
	exit 0
else				#Sinon renvoie Fn=F(n-1)+F(n-2)
	echo $((`./fibonacci.sh $(($1-1))` + `./fibonacci.sh $(($1-2))`))
fi
exit 0
