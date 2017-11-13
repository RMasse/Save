// mots_td1.c
#include "mots.h"
#include <stdio.h>
#include <string.h>

Mot abc_vide(){
Mot res=(Mot)malloc(ABC_MAX*sizeof(Lettre));
*res=fin;
return res;
}

Mot abc_ajoutfin(Mot m,Lettre l)
{
	int i; Mot res= abc_vide();
	for(i=0;i<256 && m[i]!=fin;i++)
	{
		res[i]=m[i];
	}
	res[i+1]=fin;
	res[i]=l;
	return res;
}

Nat abc_lg(Mot m){
	int i;
	for(i=0;m[i]!=fin;i++){}
	return i;
}

Lettre abc_ieme(Mot m, int i){
	return m[i-1];
}

Mot abc_concat(Mot m1, Mot m2){
	int i=abc_lg(m1);
	for(;-i!=fin;i++)
	{
		for(int j=0;m2[j]!=fin;j++)
		{
			m1[i+1]=m2[j];
		}
	}
	return m1;
}

void abc_put(Mot m){
	printf("m");
}

Mot abc_str2mot(char *m){
	int i;
	Mot res=abc_vide();
	for(i=0;i<strlen(m);i++){
		res[i]=m[strlen(m)-i];
	}
	return res;
}

bool abc_sousMot(Mot sous, Mot cont){
	int i,j;
	i=abc_lg(sous);
	j=abc_lg(cont);
	
	if(i>j){return false;}
	else
	{
		for(;j==0;j--)
		{
			if(sous[j]==cont[j])
			{
				i--;
			}
		}
		if(i==0){return true;}
		else {return false;}
	}
}

bool abc_sousChaine(Mot sous, Mot cont){
	int i=0,j=0;
	int ls=abc_lg(sous);
	int lc=abc_lg(cont);
	Mot res=abc_vide();
	
	if(ls>lc){return false;}
	else
	{
		for(;j<=lc;j++)
		{
			if(sous[j]==cont[j])
			{
				res[i]=cont[j];
				i++;
				if(res==sous){return true;}
			}
			else
			{
				res= abc_vide();
				j++;
				i=0;
			}
		}
		return false;
	}
}

bool abc_ababb_sousChaine(Mot cont){
	int etat=0;
	switch (etat)
	{
		case a:
			if(etat==0||etat==2){etat+=1;}
			if(etat==3){etat-=2;}
			if(etat==4){etat-=1;}
			break;
		
		case b:
			if(etat==1||etat==3||etat==4){etat+=1;}
			if(etat==2){etat-=2;}
			break;
			
	}
	return (etat==5);	
}

int main(){
	Mot s1=abc_vide();
	
	abc_ababb_sousChaine(s1);
	return 0;
}
