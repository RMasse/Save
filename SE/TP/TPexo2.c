#include <stdio.h>
#include <unistd.h>

#define EOF (-1)
#define TAILLE_TAMPON 1024

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
