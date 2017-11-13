#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdbool.h>
#include <fnmatch.h>

char * chemin_complet(const char * dir, const char * name){
	char * fullname = malloc(1024);
	strcpy(fullname,dir);
	if(dir[strlen(dir)-1]!='/') //Evite le doublon si '/' est déjà donné dans l'argument
		strcat(fullname,"/");
	strcat(fullname, name);
	return fullname;
}

bool is_directory(const char *path) {
    struct stat path_info;
    return lstat(path, &path_info) == 0 && S_ISDIR(path_info.st_mode);
}

char * perm2(const char * dir, const char * name){
	char * fullname = malloc(1024);
	strcpy(fullname,dir);
	strcat(fullname, name);
	return fullname;
}

int find(char *path,char *str,char *perm){
	int i=0;
	DIR *rep=opendir(path);
    if(rep != NULL)
    {	
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL) //Parcours le fichier
        {
			if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..") || ent->d_type==DT_LNK){
				continue; //Evite . et ..
			}
			char * path_filename = chemin_complet(path,ent->d_name);
			
			if (ent->d_type == DT_REG){ //Test si le fichier pointé est régulier
				
				struct stat file_info;
				
				if(stat(path_filename,&file_info)==0 && !fnmatch(str,ent->d_name,0)){
				// fnmatch traite les caractères * et ? dans les noms de fichiers
					char *p;
					int a=strtol(perm2("100",perm),&p,8); //Concatène avec 100 et convertit la variable "perm" en octal
				
					if(file_info.st_mode == a){ // pour comparer le type et protection du fichier contenu dans st_mode
						printf("%s\n",path_filename);
					}
				}
			}
			if (ent->d_type == DT_DIR){ //Test si le fichier pointé est un répertoire
				int r;
				if ((r=fork() > 0)){
					if(!is_directory(path_filename)){	
						find(path_filename,str,perm);
					}
					int status;
					if (wait(&status)==-1){
						perror("wait");
					}
					i += WEXITSTATUS(status); //compte le nb de processus utilisés
				}
				else {
					if (r==0){
						exit(find(path_filename,str,perm));
					}
					else {
						perror("fork");
						exit(1);
					}
				}
			}
		}
		closedir(rep);
	}
	return i;
}

int main(int argc, char *argv[]){
	if (argc != 4) {
        printf("Utilisation:\n\t./find SOURCE \"FICHIER\" PERMISSIONS\n");
        return 0;
    }
	find(argv[1],argv[2],argv[3]);
		
	return 0;
}
