#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BUFSIZE  1024
#define MONEOF (-1)


struct FICHIER {
	int fd;
	int writeonly;
	unsigned char buf[BUFSIZE];
	unsigned char *p;
	int taille;
};

struct FICHIER *monopen(char *nom, char *mode);
int mongetchar(struct FICHIER *f);
int monputchar(struct FICHIER *f, unsigned char c);
int monclose(struct FICHIER *f);

