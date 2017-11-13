#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#define EOF (-1)
#define TAILLE_TAMPON 1024

int getcharNbuff(void){
	unsigned char c;
	ssize_t n;
	n=read(0,&c,1);
	if(n==-1)
		return EOF;
	else if(n==0)
		return EOF;
	return c;
}

int getcharBuff(void){
	static unsigned char tampon[TAILLE_TAMPON];
	static unsigned char *tamponp= tampon;
	static ssize_t n=0;
	if(n==0){
		n=read(0,tampon,sizeof(tampon));
		tamponp=tampon;
	}
	if(--n>0){
		return *tamponp++;
	}
	else return EOF;
}

int main(){
	int a;
	while ((a=getcharBuff())!=EOF){
		putchar(a);
	}
	return 0;
}
