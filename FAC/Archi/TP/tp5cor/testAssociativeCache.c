#include <stdio.h>
#include <stdlib.h>

#include "associativeCache.h"

int main(){
  
  struct ACache * c = ACache_Create (4,2);
//   ACache_Disp(c);
  setACache(0x00000040,0xFFFFFFFF,c);
  setACache(0x00000040,0xFFFFFFFF,c);
  setACache(0x00000040,0x0000000F,c);
//   ACache_Disp(c);
//   setDCache(0x00000048,0xFFFFFFFF,c);
  printf("read 0x00000040: %d \n", lwAC(NULL,0x00000040,c));
  printf("read 0x00000044: %d \n", lwAC(NULL,0x00000044,c));
//   DCache_Disp(c);
  ACache_Delete(c);
  
  return 0;
} 
