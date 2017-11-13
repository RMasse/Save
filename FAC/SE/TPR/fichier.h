#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/wait.h>
#define BUFSIZE  1024
#define MONEOF (-1)

struct FICHIER {
	int fd;
	int writeonly;
	unsigned char buf[BUFSIZE];
	unsigned char *p;
	int taille;
};

struct FICHIER *monopen(const char *nom,const char *mode);
int mongetchar(struct FICHIER *f);
int monputchar(struct FICHIER *f, unsigned char c);
int monclose(struct FICHIER *f);

int copie_fichier (const char * src,const char *dest);
char * chemin_complet(const char * dir, const char * name);
bool is_directory(const char *path);
int copie_arbre(const char * src,const char * dest);
