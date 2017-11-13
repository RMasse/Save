#include <stdio.h>
#include <stdlib.h>

#include "directCache.h"

#define L 4 /*2^L Lignes de 4 octets ->2 bits pour l'offset*/

int main(){

  struct DCache * c = DCache_Create (L);
  DCache_Disp(c);
  setDCache(0x00000040,0xFFFFFFFF,c);
  setDCache(0x00000048,0xFFFFFFFF,c);
  printf("read 0x00000040: %d \n", lwDC(NULL,0x00000040,c));
  printf("read 0x00000044: %d \n", lwDC(NULL,0x00000044,c));
  DCache_Disp(c);
  DCache_Delete(c);

  return 0;
}
