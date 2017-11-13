#!/bin/bash



txt=`ls $1 | grep -E '.txt$' | wc -l`
c=`ls $1 | grep -E '.c$' | wc -l`
cpp=`ls $1 | grep -E '.cpp$' | wc -l`
noext=`ls $1 | grep -v '\..*' | wc -l`

echo "Il y a $txt fichier(s) dans $1 dont l'extension est .txt"
echo "Il y a $c fichier(s) dans $1 dont l'extension est .c"
echo "Il y a $cpp fichier(s) dans $1 dont l'extension est .cpp"
echo "Il y a $noext fichier(s) dans $1 sans extension"
