/*!
   \file lister.c
*/

#include <fnmatch.h>

#include "deposer.h"

char * chemin_complet(const char * dir, const char * name){
	char * fullname = malloc(1024);
	strcpy(fullname,dir);
	if(dir[strlen(dir)-1]!='/') //Evite le doublon si '/' est déjà donné dans l'argument
		strcat(fullname,"/");
	strcat(fullname, name);
	return fullname;
}

int compterFichier(DIR* dir){
    int nbr = 0;
    struct dirent* ent = NULL;
    while ((ent = readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
        nbr++; /* Alors on incrémente le compteur */
    }

    return nbr;

}

char** lister(){
	
	DIR *rep=opendir(PROJETSE);
	int i=0,j=0;
	//On compte le nb de fichiers dans le dossier et on divise par 2
	int nb=compterFichier(rep)/2; //car on ne veut récupérer que les jXXXXXX
	
	char **tab =(char **)malloc(sizeof(char *)*nb); 
	for (i=0; i<nb; i++)
		tab[i]=(char *)malloc(sizeof(char)*100);
	rewinddir(rep);
    if(rep != NULL)
    {	
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL) //Parcours le fichier
        {
			if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..") || ent->d_type==DT_LNK){
				continue; //Evite . et ..
			}
			char * path_filename = chemin_complet(PROJETSE,ent->d_name);
			
			if (ent->d_type == DT_REG){ //Test si le fichier pointé est régulier
				
				struct stat file_info;
				if(stat(path_filename,&file_info)==0 && !fnmatch("j*",ent->d_name,0)){ //Récupère les infos du fichier et renvoie 0 en cas de réussite

					FILE *file;
					char buffer[BUFFSIZE];

					if((file=fopen(path_filename,"rb"))==NULL){
						printf("cannot open this file for reading: %s.\n", ent->d_name);
					}
					size_t bytes;
					
					while ((bytes = fread(buffer, 1, BUFFSIZE, file)) != 0) {
						sprintf(tab[j],"%s",buffer);
					}
					j++;
				}
			}
		}
		closedir(rep);
	}
	return tab;
}

static void	usage(char *prog){
  fprintf(stderr, "usage: %s [-l] [-u arg]\n", prog);
  exit(1);
}

int main(int argc, char *argv[]){
	int i=0,j=0;
	char **tab =(char **)malloc(sizeof(char *)*100); 
		for (i=0; i<20; i++)
			tab[i]=(char *)malloc(sizeof(char)*100);
	tab=lister();
	if (argc == 1) {
		
        while(tab[j]!=NULL){
			char *token=strtok(tab[j]," ");
			token=strtok(NULL,"");
			printf("%s",token);
			j++;
		}
    }
    else{
		
		int errflg = 0; 
		int c; 
		char * progname = argv[0];

		while ((c = getopt(argc , argv, "lu:")) != -1){
			switch (c) {
				case 'l':
					while(tab[j]!=NULL){
						printf("%s",tab[j]);
						j++;
					}
					break;
				case 'u':
					puts("fichiers de l'user'");
					break;
				case '?':
					errflg++;
					break;
			}
			if (errflg)
				usage(progname);
		}
	}
	return 0;
}

