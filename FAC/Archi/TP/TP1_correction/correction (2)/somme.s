.data

entent: .asciiz "Veuillez entrer un premier entier plz\n"
entent2: .asciiz "Veuillez entrer un second entier plz\n"
sumest: .asciiz "La somme est "

.text

__start:

la $a0 entent   # Le registre a0 contient le pointeur vers le début de la chaine de caractère
li $v0 4   # appel système 4 -> print string
syscall

li $v0 5   # appel système 5 −> read int
syscall

move $t0 $v0  # Sauvegarde l'entier récupéré dans $v0

la $a0 entent2
li $v0 4
syscall   # Affichage n°2

li $v0 5   # appel système 5 −> read int
syscall

move $t1 $v0  # Sauvegarde l'entier récupéré dans $v0

la $a0 sumest
li $v0 4
syscall   # Affichage n°3

add $a0 $t0 $t1
li $v0 1  # appel système 1 -> print int
syscall

j KThxBye

KThxBye:
li $v0 10  # appel système 10 -> fin du programme
syscall