#include <stdlib.h>
#include <stdio.h>


#define MAX 20

int compare(int a,int b,int c){
	
	if(a>=b&&a>=c)
		return 1;
	else if(b>=a&&b>=c)
		return 2;
	else return 3;
}

int min(int a,int b,int c){
	
	if(a<=b&&a<=c)
		return 1;
	else if(b<=a&&b<=c)
		return 2;
	else return 3;
}

int rec_stra(int total,int n){
	if(total==MAX&&n==1)
		return 1;
	if(total>=MAX&&n==-1)
		return -1;
	if(total>MAX)
		return 0;

	if(n==1)
		return compare(rec_stra(total+1,-n),rec_stra(total+2,-n),rec_stra(total+3,-n));
	else 	return min(rec_stra(total+1,-n),rec_stra(total+2,-n),rec_stra(total+3,-n));


}


int strategie(int total){
	if(MAX-total<4)
		return MAX-total;

	return rec_stra(total,1);
}




int main(){
	srand(time(NULL));
	int som=0,n,o;
	while(1){
		printf("A joue : ");	
		scanf("%i",&n);
		while((som+n)>MAX||n>3||n<1){
			printf("nombre invalide :");
			scanf("%i",&n);		
			}
		som=som+n;
		printf("total : %i\n",som);
		if(som==MAX){
			printf("A gagné!\n");
			return 1;
		}
		o=strategie(som);
		som=som+o;
		printf("B joue : %i\n",o);
		printf("total : %i\n",som);
		if(som==MAX){
			printf("B gagné!\n");
			return 1;
		}
	}
}