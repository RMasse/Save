#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NOR(A,B) (!(A||B))
#define AND(A,B) (A&&B)
#define OR(A,B) (A||B)
#define NOT(A) (!A)
#define XOR(A,B) (((!A)&&B)||(A&&(!B)))

#define BIT(A,B) (((A)>>(B)&0x1))
#define SETBIT(A,B,V) A=(V? (0x1<<B)|A : (~(0x1<<B))&A )

long long int P2(int n) {
  return (n<0?0:(n==0?1 : 2*P2(n-1)));
}

/// exo1
void vecteurs_de_booleens(unsigned int nombre_de_booleens) {
  for (unsigned int i = 0; i < P2(nombre_de_booleens); ++i) {
    printf("(");
    for (unsigned int j = 0; j < nombre_de_booleens; ++j) {
      if (j)
        printf(", ");
      printf("%u", BIT(i,nombre_de_booleens-1-j));
    }
    printf(")\n");
  }
}

/// exo2
int F2(int args){
  return XOR(BIT(args,0),BIT(args,1));
}

int F3(int args){
  return OR( AND(BIT(args,0),NOT(BIT(args,1))) , OR( AND(BIT(args,1),NOT(BIT(args,2))), AND(NOT(BIT(args,1)),BIT(args,2)) ));
}

int F4(int args){
  return OR( XOR( AND(AND(BIT(args,0),BIT(args,1)), NOT(BIT(args,2)) ), AND(AND(BIT(args,0),NOT(BIT(args,1))),BIT(args,3) )  ) , AND(BIT(args,2),NOT(BIT(args,3))) );
}

/// exo3

void verite2var( int (*func) (int) ){
  int nbvar=2;
  int max = P2(nbvar);
  int i,j;
  printf(" A | B | F(A,B) \n");
  printf("---|---|-------- \n");
  for (i=0;i<max;i++) {
    for (j=0;j<nbvar;j++) printf(" %d |",BIT(i,j));
    printf("   %d   \n", func(i));
  }
}

/// exo4

void veriteNvar(int N, int (*func) (int) ){
  int nbvar=N;
  int max = P2(nbvar);
  int i,j;
  printf(" A | B | F(A,B) \n");
  for (j=0;j<nbvar;j++) printf(" X%d |",j);
  printf(" F(X0,...,X%d) \n",j-1);
  for (j=0;j<nbvar;j++) printf("----|");
  printf("------------- \n");
  for (i=0;i<max;i++) {
    for (j=0;j<nbvar;j++) printf(" %d  |",BIT(i,j));
    printf("   %d   \n", func(i));
  }
}

/// exo5

/*
 * X0 | X1 | X2 | F(X0,...,X2)
 * ---|----|----|-------------
 * 0  | 0  | 0  |   0
 * 1  | 0  | 0  |   1         <- (1)
 * 0  | 1  | 0  |   1         <- (2)
 * 1  | 1  | 0  |   1         <- (3)
 * 0  | 0  | 1  |   1         <- (4)
 * 1  | 0  | 1  |   1         <- (5)
 * 0  | 1  | 1  |   0
 * 1  | 1  | 1  |   0
 *
 * En prenant la table de vérité ci-dessus, la forme disjonctive se trouve en
 * prenant toute les lignes qui ont pour résultat «vrais».
 * C'est vrais quand : (x0 ET NON x1 ET NON x2) OU (1)
 *                     (NON x0 ET x2 et NON x3) OU (2)
 *                     ...
 */


void disjonctive( int N, int (*func) (int)) {
  int nbvar=N;
  int max = P2(nbvar);
  int i,j;
  bool first = true;
  for (i=0;i<max;i++) {
    if (func(i)){ // Le résultat est vrais donc on ajoute les termes
      if (!first)
        printf(" + (");
      else {
        printf("(");
        first = false;
      }
      for (j=0;j<nbvar-1;j++) {
        if (BIT(i,j))
          printf("X%d.", j);
        else
          printf("!X%d.", j);
      }
      if (BIT(i,j))
        printf("X%d", j);
      else
        printf("!X%d", j);
      printf(")");
    }
  }
  printf("\n");
}

/*
 * X0 | X1 | X2 | F(X0,...,X2)
 * ---|----|----|-------------
 * 0  | 0  | 0  |   0         <- (1)
 * 1  | 0  | 0  |   1
 * 0  | 1  | 0  |   1
 * 1  | 1  | 0  |   1
 * 0  | 0  | 1  |   1
 * 1  | 0  | 1  |   1
 * 0  | 1  | 1  |   0         <- (2)
 * 1  | 1  | 1  |   0         <- (3)
 *
 * En prenant la table de vérité ci-dessus, la forme conjonctive se trouve en
 * prenant toute les lignes qui ont pour résultat «faux» en les inversant.
 * C'est vrais quand c'est NON faux ;) :
 *                     NON (NON x0 ET NON x1 ET NON x2) <=> (x0 OU x1 OU x2) ET (1)
 *                     NON (NON x0 ET x1 et x2) <=> (x0 OU NON x1 OU NON x2) ET (2)
 *                     ...
 */

void conjonctive( int N, int (*func) (int)) {
  int nbvar=N;
  int max = P2(nbvar);
  int i,j;
  bool first = true;
  for (i=0;i<max;i++) {
    if (!func(i)){ // Le résultat est faux donc on ajoute son contraire
      if (!first)
        printf(" . (");
      else {
        printf("(");
        first = false;
      }
      for (j=0;j<nbvar-1;j++) {
        if (BIT(i,j))
          printf("!X%d+", j);
        else
          printf("X%d+", j);
      }
      if (BIT(i,j))
        printf("!X%d", j);
      else
        printf("X%d", j);
      printf(")");
    }
  }
  printf("\n");
}

int main(){
  /// exo1
  for (unsigned int i = 1; i < 5; ++i) {
    printf("Vecteur de %d booleens\n", i);
    vecteurs_de_booleens(i);
  }

  /// exo2
  int arg=1;
  printf("F2(%d,%d)= %d\n", BIT(arg,0),BIT(arg,1),F2(arg));
  arg=7;
  printf("F3(%d,%d,%d)= %d\n", BIT(arg,0),BIT(arg,1), BIT(arg,2),F3(arg));
  arg=8;
  printf("F4(%d,%d,%d,%d)= %d\n", BIT(arg,0),BIT(arg,1), BIT(arg,2), BIT(arg,3),F4(arg));

  /// exo3
  verite2var( F2 );

  /// exo4
  veriteNvar( 3, F3);
  veriteNvar( 4, F4);

  /// exo5
  disjonctive( 2, F2);
  disjonctive( 3, F3);
  disjonctive( 4, F3);

  conjonctive( 2, F2);
  conjonctive( 3, F3);
  conjonctive( 4, F3);
}
