/*!
   \file retirer.c
*/

#include "deposer.h"

char * chemin_complet(const char * dir, const char * name){
	char * fullname = malloc(1024);
	strcpy(fullname,dir);
	if(dir[strlen(dir)-1]!='/') //Evite le doublon si '/' est déjà donné dans l'argument
		strcat(fullname,"/");
	strcat(fullname, name);
	return fullname;
}

int main (int argc,char* argv[]) {
	if (argc <= 1) {
        printf("Utilisation:\n\t./retirer FICHIERS\n");
        return 0;
    }

	for(int i=1;i<argc;i++){
		int ret;
		char * spool = chemin_complet(PROJETSE,argv[i]);
		if((getlogin())==NULL){
			ret = remove(spool);
			if(ret == 0){
				printf("File %s deleted successfully\n",argv[i]);
			}
			else{
				printf("Cannot find id %s\n",argv[i]);
			}
		}
	}
	return 0;
}
