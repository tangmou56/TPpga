#include<stdio.h>
#include<string.h>
int palind(char string[],int deb,int fin){
	if(deb>fin)
		return 1;
	else if(string[deb]!=string[fin])
		return -1;
	else palind(string,deb+1,fin-1);	
		
}




int main(){
	char string[100];
	printf("Saisir la phrase : ");
	scanf("%s",string);
	if(palind(string,0,strlen(string)-1)>0)
		printf("C'est palindrome\n");
	else
		printf("Ce n'est pas palindrome\n");	
	
}