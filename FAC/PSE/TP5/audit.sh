#!/bin/bash

users_connect () {
        who
}
#~ Function users_connect{
                #~ who
#~ }

disk_espace () {
        df -k
}

#~ Function disk_espace{
                #~ df -k
#~ }

pause () {
        read x
}

#~ Function pause{
                #~ read x 
#~ }

while true
do
clear
echo "0 - Fin"
echo "1 - Afficher la liste des utilisateurs connectés"
echo "2 - Afficher l'espace disque"
read -p "Votre choix : " choix

case "$choix" in
0) exit 0
        ;;
1) users_connect
        ;;
2) disk_espace
        ;;
*) echo "Votre choix est incorrect"
        ;;
esac
echo " Appuyer sur entrée pour continuer"
pause
done
