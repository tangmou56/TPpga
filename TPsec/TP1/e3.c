#include<stdio.h>

int fibo_rec(int n){
	if(n==0)
		return 0;
	else if(n==1)
		return 1;
	else
		return fibo_rec(n-1)+fibo_rec(n-2);

}


int fibo_tab(int n){
	int tab[1000];
	int i;
	tab[0]=0;
	tab[1]=1;
	for(i=2;i<=n;i++)
		tab[i]=tab[i-1]+tab[i-2];
	return tab[n];
	
}





int main(){
	int n;
	printf("Calculer la valeur Fibonacci de : ");
	scanf("%i",&n);
	printf("Résultat récursive : %i\n",fibo_rec(n));
	printf("Résultat itérative avec table : %i\n",fibo_tab(n));
}
