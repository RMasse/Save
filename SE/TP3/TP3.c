#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include "check.h"
#include <string.h>

char type_fichier_linux(unsigned char c){
	switch (c){
		case DT_REG: return ('-');
		case DT_DIR: return ('d');
		case DT_BLK: return ('b');
		case DT_LNK: return ('l');
		case DT_CHR: return ('c');
		case DT_SOCK: return ('s');
	}
	return ('?');
}

char type_autre_SE(char *path,char *name){
	struct stat s;
	char *pathT;
	int tailleMalloc= strlen(path)+1+strlen(name)+1;
	
	CHECK((pathT=malloc((tailleMalloc)*sizeof(char)))!=NULL);
	sprintf(pathT,"%s/%s",path,name);
	
	CHECK(lstat(pathT,&s)==0);
	free(pathT);
	
	if(S_ISREG(s.st_mode))
		return ('-');
	else if (S_ISDIR(s.st_mode))
		return ('d');
	else if (S_ISBLK(s.st_mode))
		return ('b');
	else if (S_ISLNK(s.st_mode))
		return ('l');
	else if (S_ISCHR(s.st_mode))
		return ('c');
	else if (S_ISSOCK(s.st_mode))
		return ('s');
	else
		return ('?');
}

int main(int argc, char **argv){
	DIR *d;
	struct dirent *entre;
	
	if (argc<2){
		printf("Utilisation %s <dirname> \n",argv[0]);
		exit(1);
	}
	
	CHECK((d=opendir(argv[1]))!=NULL);
	
	while ((entre=readdir(d))){
		if (type_fichier_linux(entre->d_type)=='?'){
			printf("%c %10d %s\n", type_autre_SE(argv[1],entre->d_name),(int) entre->d_ino,entre->d_name);
		}
		else{
			printf("%c %10d %s\n", type_fichier_linux(entre->d_type),(int) entre->d_ino,entre->d_name);
		}
	}
	closedir(d);
	return 0;
}
