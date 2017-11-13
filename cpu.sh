#!/bin/sh

#version kernel
cat /proc/version

#temps écoulé depuis démarrage (soustraire les 2)
who -b | sed 's/^[ \t]*démarrage système //'
date '+%F %H:%M'

#nb d'user co
who -q

# les 5 process occupant le plus de mem
# pas fini il manque des trucs pour trier
grep VmSize /proc/[1-9][1-9][1-9][1-9]/status | sed 's/\/proc\///g' | sed 's/\/status:VmSize://g' | sort +1 -2 -rn


#les 5 plus gros fichiers depuis rep courant
sudo du -haD | sort -r | head -5
