#!/bin/bash

balaye () {
        find $HOME -size 0 -exec rm -i {}\;
}

pas_d_espace () {
        pourcent=$(df -k | grep /$ | awk '{print $5}' | tr -d %)
# grep /$ -> ligne qui termine par /
# awk  -> 5è champ de la ligne
# tr -d % -> supprimer le caractère % 
        if (( $pourcent >= 80 ));then
                return 0
        fi
        return 1
}

pause () {
        read x
}

while true
do
clear
echo "0 - Fin"
echo "1 - Supprimer les fichiers de taille 0 sous mon répertoire d'accueil"
echo "2 - Contrôler l'espace disque du système de fichiers racine"
read -p "Votre choix : " choix

case "$choix" in
0) exit 0
        ;;
1) balaye
        ;;
2) if pas_d_espace; then
        echo Alerte
else
        echo Normal
fi
        ;;
*) echo "Votre choix est incorrect"
        ;;
esac
echo "Appuyer sur Entrée pour continuer"
pause

done
