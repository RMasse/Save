#!/bin/bash

somme=0
echo "Saisir un nombre par ligne, ^d pour afficher la somme"
while read nombre
do
        if [[ $nombre != ?([+-])+([0-9]) ]]
        then
                echo "La valeur saisie n'est pas un nombre, saisir un nombre:"
                continue
        fi
        ((somme+=nombre))
done
echo "la somme est: $somme"
exit 0



