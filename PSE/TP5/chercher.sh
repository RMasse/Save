#!/bin/sh

chercher(){ #Fonction chercher
	if [ -e "$1/$2" ] #Test si le fichier existe
	then
		echo "$1/$2"
	else
		for i in `ls $1` #Boucle récursive
		do
			if [ -d "$1/$i" ]
			then
				chercher "$1/$i" $2
			fi
		done
	fi
}

chemin=$1 #Stocke le chemin rentré en 1er argument
shift #shift pour ne conserver ensuite que les noms de fichiers
err=0
for i
do
	chercher $chemin $i | grep "$i" #Appele récursivement la fonction pour chaque fichier
	if [ $? -eq 1 ] 	#Test si le code de retour de fonction vaut 1 dû à une non existence du fichier
	then			#cherché
		echo "$i not found"
		err=$(($err+1)) #Fait la somme du nombre de code de retour d'erreur
	fi
done
exit $err #Renvoie code de retour du nombre d'erreurs reçues (0 si aucune >0 sinon)
