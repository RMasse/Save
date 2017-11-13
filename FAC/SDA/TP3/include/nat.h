#include "bool.h"
#include <stdio.h>

#ifndef __NAT_H__
#define __NAT_H__

#define _Nat_ struct sn * 	//permet de définir à l'avance ce que va être
							//un Nat

struct sn {
    char f; //symbole d'opération 0 ou s
    _Nat_ p; //prédécesseur
                         };

typedef _Nat_ Nat; //un Nat est un pointeur sur une stucture sn

Nat O(); //le naturel 0
Nat s(Nat n); //fonction successeur
Nat add(Nat n, Nat m); //addition
Nat mult(Nat n, Nat m); //multiplication


Bool zero(Nat n); //test de nullité
Bool estsucc(Nat n); //test de non nullité
Bool egN(Nat n, Nat m); //test d'égalité
Bool spp(Nat n, Nat m); //strictement plus petit

void printn(Nat n); //affichage de n en unaire
Nat u2nat(unsigned u); //traduction de décimal à unaire
unsigned nat2u(Nat n); //transforme un Nat en entier non signé

#endif 
