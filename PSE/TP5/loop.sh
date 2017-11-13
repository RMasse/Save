#!/bin/sh

if [ $# -eq 2 ] #Test si il y a 2 arguments
then
	if [ $1 -le $2 ] #Test si le 1er argument et <= au 2eme argument
	then
		seq $1 $2 #Renvoie tout les nombres compris entre le 1er et le 2eme argument
	else
		seq $2 $1 #Sinon renvoie tout les nombres compris entre le 2eme et le 1er
	fi
	exit 0
elif [ $# -eq 3 ] #Test si il y a 3 arguments
then
	if [ $1 -le $2 ] #Test si le 1er argument et <= au 2eme argument
	then
		if [ $3 -gt 0 ] #Test si le 3eme argument est > 0
		then
			seq $1 $3 $2 #Renvoie tout les nombres compris entre le 1er et le 2eme argument
		else		     #avec une incrémentation positive 
			echo "mauvaise incrémentation"
			exit 1
		fi
	else			#Si le 1er argument et >= au 2eme argument
		if [ $3 -lt 0 ] #Test si le 3eme argument est < 0
		then
			seq $1 $3 $2 #Renvoie tout les nombres compris entre le 1er et le 2eme argument
		else		     #avec une incrémentation négative
			echo "mauvaise incrémentation"
			exit 1
		fi
	fi
else #Sinon affiche erreur
	echo "Pas le bon nb d'arguments"
	exit 1
fi
exit 0
