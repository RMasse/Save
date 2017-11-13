.data

entent: .asciiz "Veuillez entrer un premier entier plz\n"
entent2: .asciiz "Veuillez entrer un second entier plz\n"
sumest: .asciiz "La somme est "

.text

__start:
la $a0 entent   # Le registre a0 contient le pointeur vers le début de la chaine de caractère
jal affiche_string

jal read_int
move $t0 $v0  # Sauvegarde l'entier récupéré dans $v0

la $a0 entent2
jal affiche_string

jal read_int
move $t1 $v0  # Sauvegarde l'entier récupéré dans $v0

la $a0 sumest
jal affiche_string

add $a0 $t0 $t1
jal affiche_int

j KThxBye

# Paramètres : - $a0 l'adresse de la chaîne de caractères à afficher
# Retour : -/
affiche_string:
li $v0 4
syscall
jr $ra

# Paramètres : - $a0 l'entier à afficher
# Retour : -/
affiche_int:
li $v0 1
syscall
jr $ra

# Paramètres : -/
# Retour : - $v0 l'entier lu
read_int:
li $v0 5
syscall
jr $ra

KThxBye:
li $v0 10  # appel système 10 -> fin du programme
syscall
