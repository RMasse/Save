.data

RetChar: .asciiz "\n"
Tableau: .asciiz "Tableau de taille: "
Aladresse: .asciiz "à l'adresse: "
Adresse: .asciiz "Adresse du premier entier du tableau: "
Place: .asciiz "Place de l'entier dans le tableau: "

.text
.globl __start

__start:

li $s0 15 #nombre d'entiers dans $s0, registre temp. sauvegardé par les fonctions
move $a0 $s0
li $a1 2
jal CreerTableau
move $s1 $v0 #$s1: adresse du premier octet du tableau

##################### Affichage de l'adresse à laquelle commence le tableau
la $a0 Adresse
li $v0 4
syscall
move $a0 $s1
jal AfficheEntier
#####################

move $a0 $s0
move $a1 $s1
jal AfficheTableau

#####################test fonction CherchePlace essayer avec un tableau trié
la $a0 Place
li $v0 4
syscall
move $a0 $s0
move $a1 $s1
li $a2 5
jal CherchePlace
move $a0 $v0
jal AfficheEntier
la $a0 RetChar
li $v0 4
syscall
####################

#####################test fonction CherchePlaceRec essayer avec un tableau trié
la $a0 Place
li $v0 4
syscall
move $a0 $s0
move $a1 $s1
li $a2 5
jal CherchePlaceRec
move $a0 $v0
jal AfficheEntier
la $a0 RetChar
li $v0 4
syscall
####################

####################test de la fonction decalage
move $a0 $s0
move $a1 $s1
jal Decalage

move $a0 $s0
move $a1 $s1
jal AfficheTableau
####################

####################test de la fonction Inserer
move $a0 $s0
move $a1 $s1
li $a2 5
jal Inserer

move $a0 $s0
move $a1 $s1
jal AfficheTableau
####################

####################test de la fonction Tri
move $a0 $s0
move $a1 $s1
jal Tri

move $a0 $s0
move $a1 $s1
jal AfficheTableau
####################

j Exit

Exit:
ori $2, $0, 10
syscall

#################################Fonction CreerTableau
###entrées: $a0: taille (en nombre d'entiers) du tableau à créer
###         $a1: 0: tableau trié dans l'ordre croissant, 1: tableau trié dans l'ordre décroissant, 2: tableau quelconque
###Pré-conditions: $a0 >=0
###Sorties: $v0: adresse (en octet) du premier entier du tableau
###Post-conditions: si $a0==0, $v0 = 0x00000000
###                 les registres temp. $si sont rétablies si utilisées
CreerTableau:
#prologue: à renseigner

#corps de la fonction: à compléter
li $t1 0
beq $a0 0 fin_CreerTableau
move $t0 $a0      # Sauvegarde de la taille du tableau
li $v0 9          # Syscall 9 -> malloc, attends le nombre d'octets dans $a0
mul $a0 $a0 4     # Un tableau de n entiers requiers n*4 octets, 4 étant taille d'un entier ou mot
syscall           # Need more ram
move $t1 $v0      # Sauvegarde du pointeur du début du tableau dans $t1

beq $a1 0 init_croissant
beq $a1 1 init_decroissant
j init_alea

init_croissant:
li $t2 0
init_croissant_boucle:
beq $t2 $t0 fin_CreerTableau  # Boucle tant qu'on a pas rempli tout le tableau
mulu $t3 $t2 4                # Calcul de l'offset depuis de début du tableau
addu $t3 $t3 $t1              # Calcul de l'adresse de la case du tableau
sw $t2 0($t3)                 # Écriture de l'index dans le tableau
add $t2 $t2 1                 # On avance à la case suivante
j init_croissant_boucle

init_decroissant:
li $t2 0
init_decroissant_boucle:
beq $t2 $t0 fin_CreerTableau
mulu $t3 $t2 4
addu $t3 $t3 $t1
neg $t4 $t2                   # À la place d'écrire 0 1 2 on inverse 0 -1 -2
sw $t4 0($t3)                 # ce qui donne un tableau décroissant !
add $t2 $t2 1
j init_decroissant_boucle

init_alea:
li $t2 0
init_alea_boucle:
beq $t2 $t0 fin_CreerTableau
mulu $t3 $t2 4
addu $t3 $t3 $t1
li $v0 41                     # Appel système 41 de Mars -> entier aléatoire
syscall                       # dans $a0
sw $a0 0($t3)
add $t2 $t2 1
j init_alea_boucle

#épilogue: à renseigner
fin_CreerTableau:
move $v0 $t1
jr $ra

#########################################################

#################################Fonction CherchePlace
###entrées: $a0: taille (en nombre d'entiers) du tableau
###         $a1: adresse du premier élément du tableau
###         $a2: l'entier dont on cherche la place
###Pré-conditions: $a0 >=0,
###                le tableau est trié
###Sorties: $v0: offset (en octet) de la place à laquelle devrait se trouver l'entier dans $a2
###Post-conditions: si $a0==0, $v0 = 0
###                 les registres temp. $si sont rétablies si utilisées
CherchePlace:
#prologue: à renseigner

#corps de la fonction: à compléter
li $t0 0
beqz $a0 fin_CherchePlace

loop_CherchePlace:
beq $t0 $a0 fin_CherchePlace  # On cherche pour tout les éléments
mulu $t2 $t0 4                # Offset dans le tableau
addu $t2 $t2 $a1              # Calcul de l'adresse
lw $t2 0($t2)                 # Chargement de l'entier se trouvant dans le tableau
ble $a2 $t2 fin_CherchePlace  # Si l'entier qu'on veut insérer est plus petit on à trouvé
addu $t0 $t0 1                # Sinon on cherche sa place plus loin
j loop_CherchePlace

#épilogue: à renseigner
fin_CherchePlace:
move $v0 $t0                  # Sa place est $t0
jr $ra
#########################################################

#################################Fonction CherchePlaceRec
###entrées: $a0: taille (en nombre d'entiers) du tableau
###         $a1: adresse du premier élément du tableau
###         $a2: l'entier dont on cherche la place
###Pré-conditions: $a0 >=0,
###                le tableau est trié
###Sorties: $v0: offset (en octet) de la place à laquelle devrait se trouver l'entier dans $a2
###Post-conditions: si $a0==0, $v0 = 0
###                 les registres temp. $si sont rétablies si utilisées
CherchePlaceRec:
#prologue: à renseigner
subu $sp $sp 4
sw $ra 0($sp)
#corps de la fonction: à compléter
li $t0 0
beqz $a0 fin_CherchePlaceRec

lw $t1 0($a1)                     # On charge la valeur en début de tableau
ble $a2 $t1 fin_CherchePlaceRec   # Si elle est plus grande on a trouvé
subu $a0 $a0 1                    # Sinon on cherche dans un tableau de taille
addu $a1 $a1 4                    # n-1 en prenant comme début de tableau la
jal CherchePlaceRec               # case suivante du tableau courant
addu $t0 $v0 1                    # et on ajoute 1 à la valeur retournée
                                  # par appel récursif
#épilogue: à renseigner
fin_CherchePlaceRec:
move $v0 $t0
lw $ra 0($sp)
addu $sp $sp 4
jr $ra
#########################################################

#################################Fonction Decalage
###entrées: $a0: taille (en nombre d'entiers) du tableau
###         $a1: adresse du premier élément du tableau
###Pré-conditions: $a0 >=0,
###                les 4 octets à la suite du tableau peuvent être écris
###Sorties:
###Post-conditions: le tableau est décalé d'une case vers la droite
###                 les registres temp. $si sont rétablies si utilisées
Decalage:
#prologue: à renseigner

#corps de la fonction: à compléter
mulu $t0 $a0 4              # On calcul l'offset de l'entier suivant le tableau
addu $t0 $a1 $t0            # On calcul son adresse
loop_Decalage:
beq $t0 $a1 fin_Decalage    # Si on se trouve sur la première case du tableau on à fini
lw $t1 -4($t0)              # Sinon on charge le contenu de la case précédente
sw $t1 0($t0)               # Et on l'écrit dans la case courante
subu $t0 $t0 4              # On se décale sur la case précédente
j loop_Decalage             # On recommence

#épilogue: à renseigner
fin_Decalage:
jr $ra
#########################################################

#################################Fonction Inserer
###entrées: $a0: taille (en nombre d'entiers) du tableau
###         $a1: adresse du premier élément du tableau
###         $a2: l'entier à insérer
###Pré-conditions: $a0 >=0,
###                le tableau commençant à $a1 de taille $a0 est trié
###                les 4 octets à la suite du tableau peuvent être écris
###Sorties:
###Post-conditions: le tableau commençant à $a1, de taille $a0+1 est trié
###                 les registres temp. $si sont rétablies si utilisées
Inserer:
#prologue: à renseigner
subu $sp $sp 20
sw $ra 0($sp)
sw $s0 4($sp)
sw $s1 8($sp)
sw $s2 12($sp)
sw $s3 16($sp)
#corps de la fonction: à compléter
move $s0 $a0      # On sauvegarde les paramètres passés à notre fonction
move $s1 $a1
move $s2 $a2
jal CherchePlace  # On cherche la place à laquelle insérer l'entier

mulu $t0 $v0 4    # On calcul son offset dans le tableau
addu $a1 $s1 $t0  # On calcul son adresse
move $s3 $a1      # On sauvegarde l'adresse pour plus tard
subu $a0 $s0 $v0  # On calcul le nombre d'entiers restant à décaler vers la droite
jal Decalage      # aka taille totale - position à partir de laquelle décaler
                  # Et on décale le reste du tableau vers la droite

sw $s2 0($s3)     # Il suffit alors d'écrire l'entier à insérer au bon endroit

Inserer_trouver_place:
#épilogue: à renseigner
lw $ra 0($sp)
lw $s0 4($sp)
lw $s1 8($sp)
lw $s2 12($sp)
lw $s3 16($sp)
lw $ra 0($sp)
addu $sp $sp 20
jr $ra
#########################################################

#################################Fonction Tri
###entrées: $a0: taille (en nombre d'entiers) du tableau
###         $a1: adresse du premier élément du tableau
###Pré-conditions: $a0 >=0,
###Sorties:
###Post-conditions: le tableau commençant à $a1, de taille $a0 est trié
###                 les registres temp. $si sont rétablies si utilisées
Tri:
#prologue: à renseigner
subu $sp $sp 16
sw $ra 0($sp)
sw $s0 4($sp)
sw $s1 8($sp)
sw $s2 12($sp)
#corps de la fonction: à compléter
move $s0 $a0          # On sauvegarde les paramètres
move $s1 $a1
li $s2 1              # On commence avec un tableau de taille 1, donc trié

loop_Tri:
beq $s2 $s0 fin_Tri   # Si on a trié tout le tableau c'est gagné
mulu $t1 $s2 4        # Sinon on calcul l'offset de l'élément après le tableau trié
addu $t1 $s1 $t1      # On calcul son addresse
lw $a2 0($t1)         # On le charge dans le registre $a2
move $a0 $s2          # On charge la taille du tableau trié $a0
move $a1 $s1          # On charge l'adresse du tableau dans $a1
jal Inserer           # On insère l'entier dans le tableau trié
addu $s2 $s2 1        # On à donc un tableau trié qui est plus grand de 1 élément
j loop_Tri            # On recommence pour le reste du tableau qui n'est pas encore trié

#épilogue: à renseigner
fin_Tri:
lw $ra 0($sp)
lw $s0 4($sp)
lw $s1 8($sp)
lw $s2 12($sp)
addu $sp $sp 16
jr $ra
#########################################################


#################################Fonction AfficheTableau
###entrées: $a0: taille (en nombre d'entiers) du tableau à afficher
###Pré-conditions: $a0 >=0
###Sorties:
###Post-conditions: les registres temp. $si sont rétablies si utilisées
AfficheTableau:
#prologue:
subu $sp $sp 24
sw $s0 20($sp)
sw $s1 16($sp)
sw $s2 12($sp)
sw $a0 8($sp)
sw $a1 4($sp)
sw $ra 0($sp)

#corps de la fonction:
la $a0 Tableau
li $v0 4
syscall
lw $a0 8($sp)
jal AfficheEntier
la $a0 Aladresse
li $v0 4
syscall
lw $a0 4($sp)
jal AfficheEntier

lw $a0 8($sp)
lw $a1 4($sp)

li $s0 4
mul $s2 $a0 $s0 #$a0: nombre d'octets occupés par le tableau
li $s1 0 #s1: variable incrémentée: offset
LoopAffichage:
bge $s1 $s2 FinLoopAffichage
lw $a1 4($sp)
add $t0 $a1 $s1 #adresse de l'entier: adresse de début du tableau + offset
lw $a0 0($t0)
jal AfficheEntier
addi $s1 $s1 4 #on incrémente la variable
j LoopAffichage

FinLoopAffichage:

la $a0 RetChar
li $v0 4
syscall

#épilogue:
lw $s0 20($sp)
lw $s1 16($sp)
lw $s2 12($sp)
lw $a0 8($sp)
lw $a1 4($sp)
lw $ra 0($sp)
addu $sp $sp 24
jr $ra
#########################################################

#################################Fonction AfficheEntier
###entrées: $a0: entier à afficher
###Pré-conditions:
###Sorties:
###Post-conditions:
AfficheEntier:
#prologue:
subu $sp $sp 8
sw $a0 4($sp)
sw $ra 0($sp)

#corps de la fonction:
li $v0 1
syscall

la $a0 RetChar
li $v0 4
syscall

#épilogue:
lw $a0 4($sp)
lw $ra 0($sp)
addu $sp $sp 8
jr $ra
#########################################################
