#!/bin/bash

exec 0<etudiants.txt
IFS='|'
read titre1 titre2 titre3
printf "%-15s%-15s%10s\n" $titre1 $titre2 $titre3       #- cadré à gauche sans rien$
while read Nom UE Moyenne
do
        printf "%-15s%-15s%10d\n" $Nom $UE $Moyenne
done
exit 0
