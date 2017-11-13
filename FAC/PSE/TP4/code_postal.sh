#!/bin/bash

echo -n "Entrez un code postal:"
read cp

case "$cp" in
        67[0-9][0-9][0-9])
                echo "$cp est un code postal du bas-rhin"
                ;;
        68[0-9][0-9][0-9])
                echo "$cp est un code postal du haut-rhin"
                ;;
        [0-9][0-9][0-9][0-9][0-9])
                echo "$cp est un code postal hors Alsace"
                ;;
        *)
                echo "$cp n'est pas un code postal de France Métropolitaine"
                ;;
esac









