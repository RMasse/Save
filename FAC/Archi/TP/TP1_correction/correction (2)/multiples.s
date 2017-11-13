.data

entent: .asciiz "Veuillez entrer l'entier dont les multiples seront affichés plz\n"
entent2: .asciiz "Veuillez entrer le nombre de multiples à afficher plz\n"
space_invader: .asciiz " "

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

li $t2 1     # $t2 correspond à notre littérateur
bouclette:
bgt $t2 $t1 KThxBye      # On sort de la boucle uniquement si t2 est égale au nombre entré au clavier
mul $a0 $t2 $t0    # On obtient le bon nombre à afficher par multiplication
jal affiche_int    # On l'affiche
la $a0 space_invader  # On affiche un espace (invasif)
jal affiche_string
add $t2 $t2 1    # Ne pas oublier d'incrémenter notre iterateur
j bouclette    # De retour en début de boucle

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
