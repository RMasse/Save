#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 20

char * chemin_complet(const char * dir, const char * name){
  char * fullname = malloc(1024);
  strcpy(fullname,dir);
  strcat(fullname,"/");
  strcat(fullname, name);
  return fullname;
}

void verif(char * str){
	int i=0;
	char *mot=getenv("PATH");
	char *token;
	char **tmp=malloc(MAX*sizeof(char*));
	token=strtok(mot,":");
	
	while (token!=NULL){
			tmp[i]=chemin_complet(token,str);
			if ((access(tmp[i],F_OK))==0){
				printf("%s\n",tmp[i]);
			}
			i++;
			token=strtok(NULL,":");
	}
}

int main(int argc, char *argv[]){

	verif(argv[1]);
	return 0;
}
