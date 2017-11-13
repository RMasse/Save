#include <stdio.h>
#include <unistd.h>

#define EOF (-1)

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

int main(){
	int a;
	while ((a=getcharNbuff())!=EOF){
		putchar(a);
	}
	return 0;
}
