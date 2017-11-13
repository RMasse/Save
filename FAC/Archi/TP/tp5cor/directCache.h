#ifndef DCACHE
#define DCACHE

#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

struct Ligne {
  int tag; //étiquette
  int valid; //bit de validité
  int word; //contenu de la mémoire
};

struct DCache {
  int taille; //log en base 2 du nombre de lignes
  struct Ligne * table; //table
};

struct DCache * DCache_Create (int taille); //création d'une cache directe à 2^taille lignes

void DCache_Delete (struct DCache * c); //suppression

void DCache_Disp(struct DCache *c); //affichage

int getOffset(int adresse, struct DCache *c);

int getIndex(int adresse, struct DCache *c);

int getTag(int adresse, struct DCache *c);

int setDCache(int adresse, int mot, struct DCache *c);

int lwDC (int *registre, int adresse, struct DCache *c);

#endif 
