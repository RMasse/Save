#include "fichier.h"

struct FICHIER *monopen(char *nom, char *mode){
	int fd, modew;
	struct FICHIER *f;
	if (strcmp(mode,"r") == 0){

		fd = open (nom, O_RDONLY);
		printf("%d\n",fd);
		if (fd < 0)
			return (NULL);
		modew = 0;
	}
	else if (strcmp(mode,"w") == 0){
		fd = open (nom, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		printf("%d\n",fd);
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
	return (ret);
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
