// mots_td1.h
#include<stdbool.h>
#include<stdlib.h>

#ifndef __MOTSH__
#define __MOTSH__

#define ABC_MAX 256

typedef unsigned int Nat;

typedef enum {fin=0, a, b, c} Lettre; // fin est une lettre spéciale

typedef Lettre * Mot;  // un Mot est un pointeur avec allocation dynamique
                       // c'est ici un type mutable

Mot abc_vide(); // mot vide avec allocation mémoire de 256 Lettres
                // la fin du mot est signifiée par la lettre spéciale fin

Mot abc_ajoutfin(Mot m, Lettre l); // ajoute la lettre l à la fin de m
                                 // précondition abc_lg(m) < 254
                                 // m est modifié par effet de bord

Nat abc_lg(Mot m); // longueur du mot m

Lettre abc_ieme(Mot m, int i); // ième lettre (en partant de 0)
                               // précondition à compléter

Mot abc_concat(Mot m1, Mot m2);  // concaténation de deux mots
                                 // le mot source est modifié
                                 // et contient à la fin la concaténation

void abc_put(Mot m);		     // affichage d'un mot

Mot abc_str2mot(char *m);      // transformation du chaîne de caractères (à la C)
                               // en un nouveau mot qui est retourné                     

bool abc_sousMot(Mot sous, Mot cont);  // sous est une sous-suite de cont

bool abc_sousChaine(Mot sous, Mot cont);  // sous est un facteur (sous-chaîne) de cont

bool abc_ababb_sousChaine(Mot cont);  // sous est un facteur (sous-chaîne) de cont
#endif
