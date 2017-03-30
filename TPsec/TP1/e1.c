#include<stdio.h>

int fac(int n,int res){
	printf("Paramètre : %i  Résultat délivré : %i\n",n,res);
	if(n==1)
		return res;
	else
		fac(n-1,res*n);

}





int main(){
	int n;
	printf("Calculer la factorielle de : ");
	scanf("%i",&n);
	fac(n,1);
	return 1;
}