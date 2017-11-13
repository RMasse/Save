#ifndef BITS
#define BITS

#include <stdio.h>

#define N1(A,N) (A|(0x1<<N))
#define N0(A,N) (A&(~(0x1<<N)))
#define BIT(A,N) ((A>>N)&0x1)
#define SMOT(A,N,T) (((A) & (((0x1<<(T))-1)<<(N)))>>(N))

void afficheBits(int n);

#endif
