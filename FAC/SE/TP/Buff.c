#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define EOF (-1)

unsigned char *tampon;
int i;

int getcharBuff(){
	static unsigned char *tamponp;
	static ssize_t n=0;
	if(n==0){
		n=read(0,tampon,((size_t)i)*sizeof(tampon));
		tamponp=tampon;
	}
	if(--n>0){
		return *tamponp++;
	}
	else return EOF;
}

int main(int argc, char *argv[]){
	char a;
	i = (strtol(argv[1],NULL,0));
	tampon=malloc(i*sizeof(char));
	while ((a=getcharBuff())!=EOF){
		putchar(a);
	}
	free(tampon);
	return 0;
}
