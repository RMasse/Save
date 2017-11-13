#include "directCache.h"

struct DCache * DCache_Create (int taille) {
  struct DCache * c = (struct DCache *) malloc (sizeof( struct DCache ));
  c->taille=taille;
  int T = (c->taille==0?0:(0x1<<c->taille));
  c->table = (struct Ligne *) malloc (T*sizeof( struct Ligne ));
  int i;
  for (i=0;i<T;i++){
    c->table[i].tag=0;
    c->table[i].valid=0;
    c->table[i].word=0;
  }
  return c;
}

void DCache_Delete (struct DCache * c) {
  if (c==NULL) return;
  if (c->table == NULL) {
    free (c);
    c=NULL;
    return;
  }
  free (c->table);
  c->table=NULL;
  free (c);
  c=NULL;
  return;
}

void DCache_Disp(struct DCache *c) {
 if (c==NULL) {
   printf ("Cache directe non initialisée: %p\n", c);
   return;
 }
 printf("Nombre de ligne: %d\n", (c->taille==0?0:(0x1<<c->taille)));
 if (c->table==NULL){
   printf ("Table non initialisée: %p\n", c->table);
   return;
 }
 int i;
 int T = (c->taille==0?0:(0x1<<c->taille));
 printf ("--------------------------------Table:------------------------------------\n");
 for (i=0;i<T;i++){
  printf ("Tag: %10d | Valid: %1d | Word:",c->table[i].tag, c->table[i].valid);
  afficheBits(c->table[i].word);
 }
 printf ("--------------------------------------------------------------------------\n");
 return;
}

int getOffset(int adresse, struct DCache *c){
  (void) c;
  return SMOT(adresse,0,2);
}

int getIndex(int adresse, struct DCache *c){
  return SMOT(adresse,2,c->taille);
}

int getTag(int adresse, struct DCache *c){
  return SMOT(adresse,c->taille+2,32-(c->taille+2));
}

int setDCache(int adresse, int mot, struct DCache *c){ //adresse de 32 octets, mots de 32 octets
  if (c==NULL) return 0;
  int ligne = getIndex(adresse, c);
  c->table[ ligne ].tag = getTag(adresse,c);
  c->table[ ligne ].valid = 1;
  c->table[ ligne ].word = mot;
  return 1;
}

int lwDC (int *registre, int adresse, struct DCache *c){
  int ligne = getIndex(adresse, c);
  int tag = getTag(adresse, c);
  if ( (c->table[ligne]).valid && (c->table[ligne]).tag == tag ) { ///hit
    if (registre) *registre = (c->table[ligne]).word;
    return 1;
  }
  else { ///miss
    ///read word in memory word
    setDCache(adresse, 0, c);
    if (registre) *registre = (c->table[ligne]).word;
    return 0;
  }
}
