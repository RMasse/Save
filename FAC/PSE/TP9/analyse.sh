#!bin/bash

while true
do

clear
echo "**** Analyse du fichier ****
1. Nom de l'organisme
2. Nombre de gènes
3. Nombre de gènes sur le brin principal
4. Nombre de gènes sur le brin complémentaire
5. Séquence en bases
6. Séquence nucléique complète
7. Nombre d'apparitions d'un motif dans la séquence nucléique

8. Fin

Votre choix"

read answer
clear

case "$answer" in 
	1*) 
