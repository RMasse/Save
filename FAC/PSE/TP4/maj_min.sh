#!/bin/bash

if [[ ! -d $1 ]]; then
        echo "$1 n'est pas un répertoire"
        exit 1
fi
echo "Traitement de $1"
cd $1
for nomfic in $(ls)
do
        nouveauNom= $(echo -n $nomfic | tr '[A-Z]' '[a-z]')
        echo $nouveauNom
        mv $nomfic $nouveauNom
done
exit 0

