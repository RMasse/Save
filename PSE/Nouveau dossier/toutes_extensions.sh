#!/bin/bash

ls $1 | grep -E '\..*' > tmp
typeset -A tab
IFS='.'
while read c1 ext
do
	((tab[$ext]++))
done < tmp
for ext in ${!tab[*]}
do
	echo "Il y a ${tab[$ext]} fichier(s) dans $1 dont l'extension est $ext"
done
noext=`ls $1 | grep -v '\..*' | wc -l`
echo "Il y a $noext fichier(s) dans $1 sans extension"
rm tmp
