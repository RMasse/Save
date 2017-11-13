/*!
   \file deposer.h
*/

#ifndef _DEPOSER_H
#define _DEPOSER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#define BUFFSIZE 2048

#define PROJETSE "spool"

// Fonction qui concatène le chemin d'un fichier et son nom
char * chemin_complet(const char * dir, const char * name);

char * prefix(const char * dir, const char * name);

// Fonction qui copie un fichier src vers un fichier dest (exercice 5.3)
int copy_file (const char *src, const char * dest);

#endif
