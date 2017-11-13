/*!
   \file deposer.c
*/

#include "deposer.h"

/*!
   \fn char * chemin_complet(const char * dir, const char * name)
   \brief Programme qui concatène le chemin d'un fichier et son nom
   \param dir et name deux chaînes de caractères constantes
   \return char *
*/

char * chemin_complet(const char * dir, const char * name){
	char * fullname = malloc(2048);
	strcpy(fullname,dir);
	if(dir[strlen(dir)-1]!='/') //Evite le doublon si '/' est déjà donné dans l'argument
		strcat(fullname,"/");
	strcat(fullname, name);
	return fullname;
}

char * prefix(const char * dir, const char * name){
	char * fullname = malloc(2048);
	strcpy(fullname,dir);
	strcat(fullname, name);
	return fullname;
}

/*!
   \fn int copy_file(const char * src, const char *dest)
   \brief Programme qui recopie un fichier vers un autre fichier (exercice 5.3)
   \param src et dest deux chaînes de caractères constantes
   \return int
*/

int copy_file(const char * src, const char *dest){
	FILE *fr, *fw;
	char buffer[BUFFSIZE];

	if((fr=fopen(src,"rb"))==NULL){
		printf("cannot open this file for reading: %s.\n", src);
		return -1;
	}

	if((fw = fopen(dest, "wb")) == NULL){
		printf("cannot open this file for writing: %s.\n", dest);
		return -1;
	}
	size_t bytes;

	while ((bytes = fread(buffer, 1, BUFFSIZE, fr)) != 0) {
		size_t written = fwrite(buffer, 1, bytes, fw);
		if( written != bytes) {
			printf("error in writing.\n");
			break;
		}
	}

	fclose(fr);
	fclose(fw);

	return 0;
}

int main (int argc, char *argv[]){
	FILE * fp;
	if (argc <= 1) {
        printf("Utilisation:\n\t./deposer FICHIERS\n");
        return 0;
    }

    for(int i=1;i<argc;i++){
		char * spool = chemin_complet(PROJETSE,prefix("d","XXXXXX"));
		mkstemp(spool); //Crée le nom unique
		
		copy_file(argv[i],spool); //Copie les données dans un fichier "dXXXXXX"
		
		char * token=strtok(spool,"/");
		token=strtok(NULL,"");
		
		char * temp=malloc(sizeof(token)); 
		for(int j = 0; j<= strlen(token);j++){
			temp[j]=token[j+1]; //ne garde que la partie unique par mkstemp
		}
		
		char * job=prefix("j",temp); //Partie unique concaténée à j
		
		printf("%s\n",job);
		
		fp = fopen (chemin_complet(PROJETSE,job), "w+");
		
		struct stat file_info;
		
			if(stat(argv[i],&file_info)==0){
				fprintf(fp,"%s %s %s\t\t%s",argv[i],job,getlogin(),ctime(&file_info.st_atime));
			}
		fclose(fp);
	}

    return 0;
}
