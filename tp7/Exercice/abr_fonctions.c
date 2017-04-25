#include <abr_fonctions.h>

/*
 * Affichage des ancetres d'un noeud
 */

extern
void abr_ancetres_afficher( const abr_t * arbre , 
			    noeud_t * noeud ,
			    void (*afficher)(const void *) )
{
  /* Test d'arret */
  while( noeud_existe(noeud) )
    {
      noeud_afficher( noeud , afficher ) ;
      printf(" / " ) ; 
      noeud = abr_pere_rechercher( arbre , noeud ) ;
    }
  
  return ; 
}

/* 
 * Creation d'un arbre binaire de travail par dichotomie 
 * a partir d'une liste d'elements generiques
 */

void affec(liste_t* liste,noeud_t **racine,int deb,int fin,err_t (*fonction_affectation)( void * e1 , void * e2 )){
	if(fin%2==0){
		*racine=noeud_creer(liste[fin/2],NULL,NULL,fonction_affectation);
		affec(liste,(*racine)->gauche,0,fin/2-1,fonction_affectation);	
	}
	else{

	}
}



extern
err_t abr_dicho_creer( abr_t ** arbre , 
		       err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	
		       err_t (*fonction_destruction)( void * e) ,			
		       int (*fonction_comparaison) ( const void * e1 , const void * e2) ,
		       liste_t * liste )
{ 
  *arbre=malloc(sizeof(abr_t));
  (*arbre)->taille=0;
  (*arbre)->racine=NULL;
  (*arbre)->affecter=fonction_affectation;
  (*arbre)->detruire=fonction_destruction;
  (*arbre)->comparer=fonction_comparaison;
  affec(liste,&((*arbre)->racine),0,sizeof(liste)-1);
  printf("%i\n",sizeof(liste));



  return(OK) ; 
}

