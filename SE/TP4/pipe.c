#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc, char ** argv ){
	/* crée le tube */
	int tube[2];
	int tube2[2];
	if (pipe(tube) == -1){
		printf("pipe failed\n");
		return 1;
	}
 
	/* crée l'enfant */
	switch(fork()){
		case -1:
			printf("fork failed\n");
			exit (1);
		case 0:
			/* crée le tube */
			if (pipe(tube2) == -1){
				printf("pipe failed\n");
				return 1;
			}
			/* crée l'enfant */
			switch(fork()){
				case -1:
					printf("fork failed\n");
					exit (1);
				case 0:
					/* enfant */
					switch(fork()){
						case -1:
							printf("fork failed\n");
							exit (1);
						case 0:
							dup2(tube2[0], 0); /* connecte le coté lecture avec stdin */
							close(tube2[0]);
							close(tube2[1]); /* ferme le coté écriture */
							
							/* execute le processus (grep command) */
							execlp("wc", "wc", "-l",NULL);
							printf("wc failed"); /* si execlp return, c'est une erreur */
							exit (1);
						default:
							close(tube[0]);
							close(tube[1]);
							exit (1);
				}
				default:
					dup2(tube2[1], 1); /* connecte le coté écriture avec stdout */
					dup2(tube[0], 0); /* connecte le coté lecture avec stdin */
					
					close(tube[0]);
					close(tube[1]); /* ferme le coté écriture */
					close(tube2[0]); /* ferme le coté lecture */
					close(tube2[1]);
					
					/* execute le processus (grep command) */
					execlp("grep", "grep", argv[1],NULL);
					printf("grep failed"); /* si execlp return, c'est une erreur */
					exit (1);
			}	
		default:
			/* parent */
			close(tube[0]); /* ferme le coté lecture */
			dup2(tube[1], 1); /* connecte le coté écriture avec stdout */

			/* execute the process (ps command) */
			execlp("ps", "ps", "eaux",NULL);
			printf("ps failed"); /* si execlp return, c'est une erreur */
			close(tube[1]);
	}
	exit (1);
}
