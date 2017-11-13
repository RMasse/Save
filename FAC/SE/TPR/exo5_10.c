#include "fichier.h"

struct FICHIER *monopen(const char *nom,const char *mode){
	int fd, modew;
	struct FICHIER *f;
	if (strcmp(mode,"r") == 0){

		fd = open (nom, O_RDONLY);
		if (fd < 0)
			return (NULL);
		modew = 0;
	}
	else if (strcmp(mode,"w") == 0){
		fd = open (nom, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (NULL);
		modew = 1;
	}
	else{
		errno = EINVAL;
		return (NULL);
	}

	f = malloc (sizeof(struct FICHIER));
	f->taille = 0;
	f->p = f->buf;
	f->fd = fd;
	f->writeonly = modew; // 1 si c'est en mode writeonly, 0 sinon
	return (f);
}
static int flushbuf(struct FICHIER *f){
	if (write (f->fd, f->buf, f->taille) != f->taille){
		return (1);
	}

	f->taille = 0;
	f->p = f->buf;
	return (0);
}

int monclose(struct FICHIER *f){
	int ret = 0;
	if (f->writeonly){
		//flush buffer
		ret = flushbuf(f);
	}

	close (f->fd);
	free (f);
	return ret;
}

int mongetchar(struct FICHIER *f){
	if (f->writeonly){
		// erreur : lecture dans un fichier ouvert en écriture
		errno = EINVAL;
		return (MONEOF);
	}
	if (f->taille == 0){
		f->taille =  read(f->fd, f->buf, BUFSIZE );
		f->p = f->buf;
	}
	if (f->taille-- == 0)
		return (MONEOF);
	else
		return (*(f->p++));
}

int monputchar(struct FICHIER *f, unsigned char c){
	if (!f->writeonly){
		// erreur : lecture dans un fichier ouvert en écriture
		errno = EINVAL;
		return (MONEOF);
	}

	if (f->taille == BUFSIZE){
		//buffer plein !
		if (flushbuf(f))
			return (MONEOF);
	}
	f->taille ++;
	*f->p++ = c;
	return (c);
}

int copie_fichier (const char * src,const char *dest){
		struct FICHIER *f1, *f2;
		int c;

		f1 = monopen (src,"r");
		f2 = monopen (dest,"w");

		if (!f1 || !f2){
			perror ("erreur ouverture");
			exit (1);
		}

		while (( c =mongetchar(f1)) != MONEOF){
			monputchar (f2,c);
		}
		
		monclose (f1);
		monclose (f2);
return 0;
}

char * chemin_complet(const char * dir, const char * name){
  char * fullname = malloc(1024);
  strcpy(fullname,dir);
  strcat(fullname,"/");
  strcat(fullname, name);
  return fullname;
}

bool is_directory(const char *path) {
    struct stat path_info;
    return lstat(path, &path_info) == 0 && S_ISDIR(path_info.st_mode);
}

int copie_arbre(const char * src, const char * dest){
	DIR * rep = opendir(src);
    int count = 1;
    if(rep != NULL)
    {	
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL) //Parcours le fichier
        {
			if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..") || ent->d_type==DT_LNK){
				continue; //Evite . et ..
			}
			char * src_filename = chemin_complet(src,ent->d_name);
			char * dest_filename = chemin_complet(dest,ent->d_name);
			
			if (ent->d_type == DT_REG){ //Test si le fichier pointé est régulier
					copie_fichier(src_filename,dest_filename);
			}
			if (ent->d_type == DT_DIR){ //Test si le fichier pointé est un répertoire
				int r;
				if ((r=fork() > 0)){
					if (!is_directory(dest_filename)){ //Si dest n'est pas un répertoire dans le fichier de destination
						mkdir(dest_filename, 0777);   // alors on le crée
						copie_arbre(src_filename,dest_filename);  // et on refait copie_arbre car peut-être qu'il y a des sous-dossier
					}
					int status;
					if (wait(&status)==-1){
						perror("wait");
					}
					count += WEXITSTATUS(status); //compte le nb de processus utilisés
				}
				else {
					if (r==0){
						exit(copie_arbre(src_filename,dest_filename));
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

return count;
}
