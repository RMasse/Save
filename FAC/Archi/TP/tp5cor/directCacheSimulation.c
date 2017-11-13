#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "directCache.h"

int rand_Adresse(int inf, int supp){
  int interval = supp-inf;
  int adresse = (rand() % interval )+ inf;
  return adresse;
}


int main(void){
 srand (time(NULL));
 struct DCache * c = DCache_Create (7);
 int nblw=1000000;
 int infaddr=0x00000000;
 int suppaddr=0x00000FFF;
  int nbhit=0;
  int nbmiss=0;
  int adresse;
//   DCache_Disp(c);
  for (int l = 0;l<nblw;l++){
    adresse=rand_Adresse(infaddr, suppaddr);
//     printf("adresse: %x\n", adresse);
    if (lwDC(NULL,adresse, c)) nbhit++;
    else nbmiss++;
  }
//   DCache_Disp(c);
  printf("lectures: %10d, hits: %10d, misses: %10d \n", nblw, nbhit, nbmiss);
  DCache_Delete(c);

  for (int i = 1; i < 7; ++i) {
    size_t num_cache_miss = 0;
    size_t num_cache_hit = 0;
    printf("\nCache avec 4 mots par ligne et %u lignes\n", (1<<i));
    c = DCache_Create (i);
    for (int j = 0; j < 200; ++j) {
      for (int k = 0; k < 200; ++k) {
        int adresse = j*200+k;
        if (lwDC(NULL, adresse, c))
          num_cache_hit += 1;
        else
          num_cache_miss += 1;
      }
    }
    float hit_percent = (float) num_cache_hit / (float) (num_cache_miss + num_cache_hit);
    printf("Acces en lignes colonnes hit %f%%, miss %f%%\n", hit_percent*100.f, (1.f-hit_percent)*100.f);
    DCache_Delete(c);
    c = DCache_Create (i);
    for (int k = 0; k < 200; ++k) {
      for (int j = 0; j < 200; ++j) {
        int adresse = j*200+k;
        if (lwDC(NULL, adresse, c))
          num_cache_hit += 1;
        else
          num_cache_miss += 1;
      }
    }
    hit_percent = (float) num_cache_hit / (float) (num_cache_miss + num_cache_hit);
    printf("Acces en colonnes lignes hit %f%%, miss %f%%\n", hit_percent*100.f, (1.f-hit_percent)*100.f);
    DCache_Delete(c);
  }

 return 0;
}
