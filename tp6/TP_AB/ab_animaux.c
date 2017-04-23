#include <ab_animaux.h>

/*
 * Affichage 
 */


void afficher(const noeud_t * racine ,
			  void (*fonction_affichage)(const void *),int haut,int rep){
	int i;
	if(racine!=NULL){
		for (i=0;i<haut;i++){
			printf("|----");
		}
		if(rep==1)
			printf("[oui]");
		if(rep==2)
			printf("[non]");
		fonction_affichage(racine->etiquette);
		printf("\n");
		
		afficher(racine->gauche,fonction_affichage,haut+1,1);
		
		
		afficher(racine->droit,fonction_affichage,haut+1,2);
		
	}
}

extern 
void ab_animaux_afficher( const ab_t * arbre , 
			  void (*fonction_affichage)(const void *))
{
	afficher(arbre->racine,fonction_affichage,0,0);
  return ; 
}

/*
 * Reconnaissance 
 */


void reco( noeud_t ** racine ,
		  err_t (*fonction_affectation)(void * , void *),void (*fonction_affichage)(const void *)){
	int rep;
	char str[100];
	if(*racine!=NULL){
		fonction_affichage((*racine)->etiquette);
		printf("\n");
		if(!noeud_feuille(*racine)){
			printf("reponse : 1-oui 2-non: ");
			scanf("%i",&rep);

				
			if(rep==1){
				if((*racine)->gauche!=NULL)
					reco((&(*racine)->gauche),fonction_affectation,fonction_affichage);
				else{
					printf("Je donne ma langue au chat.\nQuelle est la reponse? :");
					scanf("%s",str);
					string_t *str_t=string_creer(str);
					noeud_t * noeud1=noeud_creer(25,str_t ,NULL ,NULL ,string_referencer_cb );
					(*racine)->gauche=noeud1;
				}
			}
			else{
				if((*racine)->droit!=NULL)
					reco((&(*racine)->droit),fonction_affectation,fonction_affichage);
				else{
					printf("Je donne ma langue au chat.\nQuelle est la reponse? :");
					scanf("%s",str);
					string_t *str_t=string_creer(str);
					noeud_t * noeud1=noeud_creer(25,str_t ,NULL ,NULL ,string_referencer_cb );
					(*racine)->droit=noeud1;
				}
			}
			
		}
		else{
			printf("reponse : 1-oui 2-non: ");
			scanf("%i",&rep);
			if(rep==2){
				printf("Je donne ma langue au chat.\nQuelle est la reponse? :");
				scanf("%s",str);
				string_t *str_t=string_creer(str);
				noeud_t * noeud1=noeud_creer(25,str_t ,NULL ,NULL ,string_referencer_cb );
				printf("Donnez une question dont la reponse est oui pour '");
				fonction_affichage(noeud1->etiquette);
				printf("'");
				printf(" et non pour '");
				fonction_affichage((*racine)->etiquette);
				printf("':");
				scanf("%s",str);
				str_t=string_creer(str);
				
				noeud_t * noeud2=noeud_creer(26,str_t ,noeud1 ,*racine ,string_referencer_cb );
				
				*racine=noeud2;
				
			}
		}
	}
}


extern 
void ab_animaux_reconnaitre( ab_t * arbre , 
			     err_t (*fonction_affectation)(void * , void *) ,
			     void (*fonction_affichage)(const void *)) 
{
	reco(&(arbre->racine),fonction_affectation,fonction_affichage);

  return ; 
}
