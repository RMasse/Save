#include "include/nat.h"
#include <stdlib.h>

Nat O(){ //le naturel 0
	Nat zero=(Nat)malloc(sizeof(struct sn));
	zero->f='0';
	zero->p=NULL;
	return zero;
}

Nat s(Nat n){ //fonction successeur
	Nat succ=(Nat)malloc(sizeof(struct sn));
	succ->f='s';
	succ->p=n;
	return succ;
}

Nat add(Nat n, Nat m){ //addition
	return (n->f=='0')? m : s(add(n->p,m));	
}
	
Nat mult(Nat n, Nat m){ //multiplication
	return (n->f=='0')? n : add(mult(n->p,m),m);
}

Bool zero(Nat n){ //test de nullité
	return n->f=='0';
}

Bool estsucc(Nat n){ //test de non nullité
	return n->f!='0';
}

Bool egN(Nat n, Nat m){ //test d'égalité
	return (n==m);
}

Bool spp(Nat n, Nat m){ //strictement plus petit
	return (n<m);
}

void printn(Nat n){ //affichage de n en unaire
	if(zero(n))
		printf("0");
	else{
		printf("s("); printn(n->p); printf(")");
	}
	return;
}

Nat u2nat(unsigned u){ //traduction de décimal à unaire
	//~ Nat n=(Nat)malloc(sizeof(struct sn));
	//~ n->f='s';
	//~ n->p=O();
	//~ for(int i=u; i!=0; i--){
		//~ n->p=s(n->p);
	//~ }
	//~ return n;
	return (u==0)? O() : s(u2nat(u-1));
}
		
unsigned nat2u(Nat n){ //transforme un Nat en entier non signé
	return (n->f=='0')? 0 : 1+nat2u(n->p);
}


