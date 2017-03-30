#include<stdio.h>

int nb_chiffre(int n){
	if(n==0)
		return 0;
	else
		return 1+nb_chiffre(n/10);

}



int main(){
	int n;
	printf("Donnez un entier positif : ");
	scanf("%i",&n);
	n=nb_chiffre(n);
	printf("Ce nombre possède %i chiffres\n",n);

}