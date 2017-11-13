#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "associativeCache.h"

int rand_Adresse(int inf, int supp){
  int interval = supp-inf;
  int adresse = (rand() % interval )+ inf;
  return adresse;
}

int main(void) {
 srand (time(NULL));
 struct ACache * c = ACache_Create (7,2);
 int nblw=1000000;
 int infaddr=0x00000000;
 int suppaddr=0x00000FFF;
  int nbhit=0;
  int nbmiss=0;
  int adresse;
//   DCache_Disp(c);
  for (int l=0; l<nblw; l++){
    adresse=rand_Adresse(infaddr, suppaddr);
//     printf("adresse: %x\n", adresse);
    if (lwAC(NULL,adresse, c)) nbhit++;
    else nbmiss++;
  }
//   DCache_Disp(c);
  printf("lectures: %10d, hits: %10d, misses: %10d \n", nblw, nbhit, nbmiss);
  ACache_Delete(c);

  for (int i = 3; i < 10; ++i) {
    size_t num_cache_miss = 0;
    size_t num_cache_hit = 0;
    printf("\nCache avec 4 mots par ligne et %u lignes\n", (1<<5));
    c = ACache_Create (i, 5);
    for (int j = 0; j < 200; ++j) {
      for (int k = 0; k < 200; ++k) {
        int adresse = j*200+k;
        if (lwAC(NULL, adresse, c))
          num_cache_hit += 1;
        else
          num_cache_miss += 1;
      }
    }
    float hit_percent = (float) num_cache_hit / (float) (num_cache_miss + num_cache_hit);
    printf("Acces en lignes colonnes hit %f%%, miss %f%%\n", hit_percent*100.f, (1.f-hit_percent)*100.f);
    ACache_Delete(c);
    c = ACache_Create (i, 5);
    for (int k = 0; k < 200; ++k) {
      for (int j = 0; j < 200; ++j) {
        int adresse = j*200+k;
        if (lwAC(NULL, adresse, c))
          num_cache_hit += 1;
        else
          num_cache_miss += 1;
      }
    }
    hit_percent = (float) num_cache_hit / (float) (num_cache_miss + num_cache_hit);
    printf("Acces en colonnes lignes hit %f%%, miss %f%%\n", hit_percent*100.f, (1.f-hit_percent)*100.f);
    ACache_Delete(c);
  }

 return 0;
}
