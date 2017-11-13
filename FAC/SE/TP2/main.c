#include "TP2.c"

int main (int argc, char *argv[]){
		struct FICHIER *f1, *f2;
		int c;

		char *d1 = argv[1];
		char *d2 = argv[2];


		f1 = monopen (d1,"r");
		f2 = monopen (d2,"w");

		if (!f1 || !f2){
			perror ("erreur ouverture");
			exit (1);
		}

		while (( c =mongetchar(f1)) != MONEOF)
			monputchar (f2,c);

		monclose (f1);
		monclose (f2);
return 0;
}
