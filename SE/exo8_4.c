#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int pid;
int pipe1[2];
int pipe2[2];

void exec1() {
	// entree de stdin (deja fait)
	// sortie de pipe1
	dup2(pipe1[1], 1);
	// ferme le pipe
	close(pipe1[0]);
	close(pipe1[1]);
	// exec
	execlp("ps", "ps", "eaux", NULL);
	// si exec ne fonctionne pas, exit
	perror("bad exec ps");
	exit(1);
}

void exec2(char * val) {
	// entree de pipe1
	dup2(pipe1[0], 0);
	// sortie de pipe2
	dup2(pipe2[1], 1);
	// ferme les 2 pipe
	close(pipe1[0]);
	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe2[1]);
	// exec
	execlp("grep", "grep", val, NULL);
	// si exec ne fonctionne pas, exit
	perror("bad exec grep");
	exit(1);
}

void exec3() {
	// entree de pipe2
	dup2(pipe2[0], 0);
	// sortie de stdout (deja fait)
	// ferme pipe2
	close(pipe2[0]);
	close(pipe2[1]);
	// exec
	execlp("wc", "wc", "-l", NULL);
	// si exec ne fonctionne pas, exit
	perror("bad exec wc -l");
	exit(1);
}

int main(int argc,char *argv[]) {
	char *val=argv[1];
	// creation de pipe1
	if (pipe(pipe1) == -1) {
		perror("bad pipe1");
		exit(1);
	}

	// fork (ps eaux)
	switch (pid = fork()) {
		case -1:
			perror("bad fork1");
			exit(1);
		case 0:
			// stdin --> ps --> pipe1
			exec1();
		default:
		// parent

		// creation de pipe2
		if (pipe(pipe2) == -1) {
			perror("bad pipe2");
			exit(1);
		}

		// fork (grep arg)
		switch (pid = fork()) {
			case -1:
				perror("bad fork2");
				exit(1);
			case 0 :
				// pipe1 --> grep --> pipe2
				
				exec2(val);
			default:
			// parent

			// ferme pipe1 inutilisé
			close(pipe1[0]);
			close(pipe1[1]);

			// fork (wc -l)
			switch (pid = fork()) {
				case -1 :
					perror("bad fork3");
					exit(1);
				case 0 :
					// pipe2 --> wc --> stdout
					exec3();
				default:
				// parent
				return 0;
			}
		}
	}
}

