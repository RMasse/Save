#ifndef ACACHE
#define ACACHE

#include <stdio.h>
#include <stdlib.h>
#include "directCache.h"


struct ACache {
  int nbTable; //nombre de voies
  struct DCache ** DTable; //tableau de caches directes
};

struct ACache * ACache_Create (int taille, int nbTable);

void ACache_Delete (struct ACache * c);

void ACache_Disp(struct ACache *c);

int setACache(int adresse, int mot, struct ACache *c);

int lwAC(int *registre, int adresse, struct ACache *c);

#endif 
