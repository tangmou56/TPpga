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
      noeud_afficher( noeud , afficher,1 ) ;
      printf(" / " ) ; 
      noeud = abr_pere_rechercher( arbre , noeud ) ;
    }
  
  return ; 
}

/* 
 * Creation d'un arbre binaire de travail par dichotomie 
 * a partir d'une liste d'elements generiques
 */

void affec(void** liste,noeud_t **racine,int deb,int fin,err_t (*fonction_affectation)( void * e1 , void * e2 )){

	if(deb>=fin){
		*racine=noeud_creer(liste[deb],NULL,NULL,fonction_affectation);
		
	}
	else if(deb+1==fin){
		*racine=noeud_creer(liste[fin],NULL,NULL,fonction_affectation);
		(*racine)->gauche=noeud_creer(liste[deb],NULL,NULL,fonction_affectation);
	}
	else{
		/*if((fin-deb)%2==0){*/
		
			*racine=noeud_creer(liste[deb+((fin-deb)/2)],NULL,NULL,fonction_affectation);
			affec(liste,(&(*racine)->gauche),deb,deb+((fin-deb)/2)-1,fonction_affectation);
			affec(liste,(&(*racine)->droit),deb+((fin-deb)/2)+1,fin,fonction_affectation);	
		/*}
		else{
			*racine=noeud_creer(liste[deb+(fin-deb)/2],NULL,NULL,fonction_affectation);
			affec(liste,(&(*racine)->gauche),deb,deb+((fin-deb)/2)-1,fonction_affectation);
			affec(liste,(&(*racine)->droit),deb+((fin-deb)/2)+1,fin,fonction_affectation);	
		}*/
	}
}



extern
err_t abr_dicho_creer( abr_t ** arbre , 
		       err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	
		       err_t (*fonction_destruction)( void * e) ,			
		       int (*fonction_comparaison) ( const void * e1 , const void * e2) ,
		       liste_t * liste,
		       int size )
{ 
  *arbre=malloc(sizeof(abr_t));
  (*arbre)->taille=0;
  (*arbre)->racine=NULL;
  (*arbre)->affecter=fonction_affectation;
  (*arbre)->detruire=fonction_destruction;
  (*arbre)->comparer=fonction_comparaison;
  affec(liste->liste,&((*arbre)->racine),0,size-1,fonction_affectation);
  



  return(OK) ; 
}

