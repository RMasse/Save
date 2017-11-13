#!/bin/sh

for i in `./loop.sh $1 $2 $3` #Fait la somme de tout les nombres compris entre
do			      #le 1er argument et le 2eme argument
	a=$((i+a))
done
echo "la somme de $1 à $2 vaut $a"
