#include <noeud.h>


/* Numero */

extern 
int noeud_numero_lire( const noeud_t * noeud ) 
{
  if(noeud!=NULL)
  	return noeud->numero;
  return(0) ; 
}

extern 
err_t noeud_numero_ecrire( noeud_t * noeud , const int numero ) 
{
  if(noeud!=NULL)
  	noeud->numero=numero;
  return(OK) ; 
}

/* Etiquette */

extern 
void * noeud_etiquette_lire( const noeud_t * noeud ) 
{
   if(noeud!=NULL)
	return noeud->etiquette;

  return(NULL) ; 
}

extern 
err_t noeud_etiquette_ecrire( noeud_t * noeud , 
			      void * etiquette ,
			      err_t (*affecter)( void * e1 , void * e2 ) ) 
{
  if(noeud!=NULL)  
	affecter(&(noeud->etiquette),etiquette);
  return(OK) ; 
}

/* Sous arbre gauche */

extern 
noeud_t * noeud_sag_lire( const noeud_t * noeud ) 
{
  if(noeud!=NULL)
	return noeud->gauche;
  return(NULL) ; 
}

extern 
err_t noeud_sag_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_gauche ) 
{
   if(noeud!=NULL)
	noeud->gauche=sous_arbre_gauche;

  return(OK) ; 
}

/* Sous arbre droit */

extern 
noeud_t * noeud_sad_lire( const noeud_t * noeud ) 
{
  if(noeud!=NULL)
	return noeud->droit;

  return(NULL) ; 
}

extern 
err_t noeud_sad_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_droit ) 
{
  if(noeud!=NULL)
	noeud->droit=sous_arbre_droit;

  return(OK) ; 
}

/*
 * Existance ?
 */

booleen_t
noeud_existe( const noeud_t * noeud )
{
   if(noeud!=NULL)
	return VRAI;

  return(FAUX) ; 
}

/* 
 * Feuille ?
 */
extern 
booleen_t noeud_feuille( const noeud_t * noeud )
{
  if(noeud!=NULL){
	if(noeud->gauche==NULL&&noeud->droit==NULL)
	return VRAI;
  }	

  return(FAUX) ; 
}

/* 
 * Parents ?
 */

extern
booleen_t noeud_est_pere( const noeud_t * noeud_pere , 
			  const noeud_t * noeud_fils ) 
{
   if(noeud_pere!=NULL&&noeud_fils!=NULL){
	if(noeud_pere->gauche==noeud_fils||noeud_pere->droit==noeud_fils)
		return VRAI;
   }
  return(FAUX) ; 
}

/* 
 * Creation
 */

extern 
noeud_t * noeud_creer( const int numero , 
		       void * etiquette , 
		       noeud_t * sous_arbre_gauche ,
		       noeud_t * sous_arbre_droit ,
		       err_t (*affecter)( void * e1 , void * e2 ) )
{
  noeud_t * noeud = NULL ; 
  noeud=malloc(sizeof(noeud_t));
  noeud->gauche=sous_arbre_gauche;
  noeud->droit=sous_arbre_droit;
  noeud->numero=numero;
  noeud->etiquette=NULL;
  affecter(&(noeud->etiquette),etiquette);
    

 
  return( noeud ) ;
}

/*
 * Destruction 
 */

extern 
err_t noeud_detruire( noeud_t ** noeud , 
		      err_t (*detruire)( void * e) ) 
{
   if((*noeud)!=NULL){
	noeud_detruire(&((*noeud)->gauche),detruire);
	noeud_detruire(&((*noeud)->droit),detruire);
	detruire(&((*noeud)->etiquette));
	free((*noeud));
	*noeud=NULL;
   }
 	
  return(OK) ; 
}

/*
 * Affichage 
 */

extern
void noeud_afficher( const noeud_t * noeud ,
		     void (*afficher)(const void *) ) 
{
  if(noeud!=NULL){
	afficher(noeud->etiquette);
	noeud_afficher(noeud->gauche,afficher);
	noeud_afficher(noeud->droit,afficher);


  }
}

/*
 * Sauvegarde dans un fichier 
 */

extern 
err_t noeud_fd_sauver( noeud_t * noeud  ,	                  /* Noeud a sauvegarder */
		       FILE * fd , 		                  /* Descripteur fichier  */
		       err_t (*sauver)( void * e, FILE *  desc) ) /* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ;

  if( ! noeud_existe( noeud ) ) 
    return(OK) ; 

  fprintf( fd , "%d " , noeud->numero ) ;
  noeud_t * fils_gauche  = noeud_sag_lire( noeud ) ;
  noeud_t * fils_droit   = noeud_sad_lire( noeud ) ;

  if( noeud_existe( fils_gauche ) )
    fprintf( fd , "%d " ,  noeud_numero_lire(fils_gauche) ) ; 
  else
    fprintf( fd , "-1 " ) ; 

  if( noeud_existe( fils_droit ) )
    fprintf( fd , "%d " ,  noeud_numero_lire(fils_droit) ) ; 
  else
    fprintf( fd , "-1 " ) ; 

  if( ( noerr = sauver( noeud->etiquette , fd ) ) )
    return(noerr) ; 

  return(OK) ; 
}

/*
 * Recherches d'un noeud dans un arbre 
 */


/* Sur le numero */

extern
booleen_t noeud_numero_rechercher( noeud_t ** result ,        /* Resultat: @ du noeud trouve */  
				   noeud_t * racine ,  /* Racine de l'arbre de recherche */
				   const int numero       )  /* Numero a rechercher dans l'arbre */
{
  if(racine!=NULL){
	if(racine->numero==numero){
		*result=racine;
		return VRAI;
	}
	if(!(noeud_numero_rechercher(result,racine->gauche,numero))){
			if(noeud_numero_rechercher(result,racine->droit,numero))
				return VRAI;
		}
	else
		return VRAI;		
  }
  return(FAUX) ; 
}


/* Sur l'etiquette */

extern
booleen_t noeud_rechercher( noeud_t ** result ,			 /* Resultat: @ du noeud trouve */  
			    noeud_t * racine  ,	         /* Racine de l'arbre de recherche */
			    void * etiquette     ,		 /* Valeur a rechercher dans l'arbre */
			    int (*comparer)(void * n1 , void * n2) ) /* Fonction de comparaison des etiquettes */
{
  if(racine!=NULL){
	if(comparer(racine->etiquette,etiquette)){
		*result=racine;
		return VRAI;
	}
	if(!(noeud_rechercher(result,racine->gauche,etiquette,comparer)))
		noeud_rechercher(result,racine->droit,etiquette,comparer);	
  }
  return(FAUX) ; 
}
