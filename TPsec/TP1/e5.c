#include<stdio.h>
#define N 20

void permuter(int * n1,int * n2){
	int w;
	w=*n1;
	*n1=*n2;
	*n2=w;
}



void tri(int *tab,int n){
	
	if (n<N){
		if(tab[n]>tab[n+1]){
			permuter(&tab[n],&tab[n+1]);
			tri(tab,0);
		}
		else
			tri(tab,n+1);
	}	


}


int main(){
	int tab[N]={1,5,2,15,2,46,7,9,2,-6,9,6,8,32,12,11,7,9,28,17};
	int i;
	printf("Tableau avant tri : ");
	for(i=0;i<N;i++)
		printf("%i ",tab[i]);
	printf("\n");
	tri(tab,0);
	printf("Tableau après tri : ");
	for(i=0;i<N;i++)
		printf("%i ",tab[i]);
	printf("\n");


}