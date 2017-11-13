#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned char *buf;
int i;

int getchar2(){
    static unsigned char *c;
    static ssize_t n = 0;
    if (n==0){
      n=read(0, buf, ((size_t)i)*sizeof(buf));
      c=buf;
    }
    if(--n >= 0)return *c++; else return EOF;
}

int main(int argc, char *argv[]){
    char c1;
    i = strtol(argv[1], NULL, 0);
    if(i>1)buf = malloc(i*sizeof(char));
    while((c1=getchar2())!=EOF){
      putchar(c1);
    }
    //free(buf);
    return 0;
}
