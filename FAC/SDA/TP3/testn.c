#include "include/nat.h"
#include <stdio.h>

int main() {
	Nat n1 = s(s(s(s(O())))), n2 = s(s(s(O())));
	Nat s = add(n1,n2);
	printn(s); printf("\n");
	printf("resultat %u et %u\n", nat2u(s), nat2u(mult(n2,s)));
	printn(mult(n2,s)); printf("\n");
	Nat n = u2nat(350), m = u2nat(700);
	printf("resultat %u\n", nat2u(mult(n,m)));
	return 0; 
}
