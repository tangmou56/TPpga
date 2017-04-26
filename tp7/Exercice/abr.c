#include <abr.h>

extern
noeud_t * abr_racine_lire( const abr_t * arbre ) 
{
  if(arbre!=NULL)
	return arbre->racine;
  return(NULL) ; 
}

extern
err_t abr_racine_ecrire( abr_t * arbre , 
			noeud_t * racine ) 
{
  if(arbre!=NULL)
	arbre->racine=racine;
  return(OK) ; 
}

extern
int abr_taille_lire( const abr_t * arbre ) 
{
  if(arbre!=NULL)
	return arbre->taille;
  return(0) ; 
}

extern
err_t abr_taille_incrementer( abr_t * arbre ) 
{
  if(arbre!=NULL)
	arbre->taille++;
  return(OK);
}

extern
err_t abr_taille_decrementer( abr_t * arbre ) 
{
  if(arbre!=NULL)
	arbre->taille--;
  return(OK);
}


/*
 * Tests
 */

extern
booleen_t abr_existe( const abr_t * arbre )
{
  if( arbre == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

extern
booleen_t abr_vide( const abr_t * arbre )
{
  if(arbre!=NULL){
	if(arbre->racine==NULL)
  		return VRAI; 
  }
  return(FAUX) ; 
}

/*
 * Creation 
 */

extern
abr_t * abr_creer( err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/*!< Fonction d'affectation d'un element */
		   err_t (*fonction_destruction)( void * e) ,			/*!< Fonction de destruction d'un element */
		   int (*fonction_comparaison) ( const void * e1 , const void * e2) )		/*!< Fonction de comparaison de 2 elements */
{
  abr_t * arbre = NULL ; 
  arbre=malloc(sizeof(abr_t));
  arbre->taille=0;
  arbre->racine=NULL;
  arbre->affecter=fonction_affectation;
  arbre->detruire=fonction_destruction;
  arbre->comparer=fonction_comparaison;
  return(arbre) ; 
}


/*
 * Destruction 
 */


extern 
err_t abr_detruire( abr_t ** arbre ) 
{
  if(*arbre!=NULL){
  	noeud_detruire( &((*arbre)->racine) , (*arbre)->detruire ); 
  	free(*arbre);
  	(*arbre)=NULL;
  }
  return(OK) ; 
}

/*
 * Affichage 
 */



extern 
void abr_afficher( const abr_t * arbre , 
		  void (*fonction_affichage)(const void *) ,
		  const ab_parcours_t parcours ) 
{
  int par;
  if(parcours==PREFIXE)
  	par=1;
  else if(parcours==POSTFIXE)
  	par=2;
  else
  	par=3;
  noeud_afficher( arbre->racine ,fonction_affichage,par );
  return ; 
}


/*
 * Insertion d'une valeur dans un ABR
 */


void inser(noeud_t **racine,void *etiquette,int (*comparer)(void * e1 , void * e2),
			err_t (*fonction_affectation)( void * e1 , void * e2 ) ){
	if(*racine!=NULL){
		
		if(comparer(&((*racine)->etiquette),(&etiquette))>0){
			inser(&((*racine)->gauche),etiquette,comparer,fonction_affectation);
		}
		else{
			inser(&((*racine)->droit),etiquette,comparer,fonction_affectation);
		}
	}
	else{
		
		*racine=noeud_creer(etiquette,NULL,NULL,fonction_affectation);
	}
}



extern
err_t abr_inserer( abr_t * arbre  ,
		   void * etiquette  ) 
{ 
  inser(&(arbre->racine),etiquette,arbre->comparer,arbre->affecter);
  return(OK) ; 
}

/*
 * Suppression d'une valeur dans un ABR
 */
 void gauche_max(noeud_t ** result,noeud_t *racine){
 	if(racine->droit!=NULL){
 		gauche_max(result,racine->droit);
 	}
 	else
 		*result=racine;
 }
 
 
 
void supp(noeud_t **noeud,err_t (*detruire)( void * e),abr_t * arbre){
	noeud_t *pere;
	noeud_t *w;
	if(noeud_feuille(*noeud)){
		pere=abr_pere_rechercher(arbre ,*noeud );
		if(pere->gauche==*noeud)
			pere->gauche=NULL;
		else
			pere->droit=NULL;
		detruire(&((*noeud)->etiquette));
		free(*noeud);
		*noeud=NULL;
	}
	else if((*noeud)->gauche==NULL&&(*noeud)->droit!=NULL){
		pere=abr_pere_rechercher(arbre ,*noeud );
		pere->droit=(*noeud)->droit;
		detruire(&((*noeud)->etiquette));
		free(*noeud);
		*noeud=NULL;
	}
	else if((*noeud)->droit==NULL&&(*noeud)->gauche!=NULL){
		pere=abr_pere_rechercher(arbre ,*noeud );
		pere->gauche=(*noeud)->gauche;
		detruire(&((*noeud)->etiquette));
		free(*noeud);
		*noeud=NULL;
	}
	else{
		gauche_max(&w,(*noeud)->gauche);
		
		
		supp(&w,detruire,arbre);

	}

}


extern 
booleen_t abr_supprimer( abr_t * arbre ,
			 void * etiquette) 
{
  booleen_t trouve = FAUX ;
  noeud_t* result;
  trouve=abr_rechercher( &result , arbre ,etiquette );
  
  
  	
  if(trouve){
  	supp(&result,arbre->detruire,arbre);
  }
  
  return(trouve) ;
} 

/*
 * Chargement d'un arbre a partir d'un fichier 
 */

extern 
err_t abr_charger( abr_t ** arbre  ,						    /* Arbre Binaire d'elements a charger */
		   char *  nom_fichier ,					    /* Nom du fichier de chargement */
		   err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	    /* fonction d'affectation d'un element */ 
		   err_t (*fonction_destruction)(void * e) ,			    /* fonction de destruction d'un element */
		   int (*fonction_comparaison) ( const void * e1 , const void * e2) , /* fonction de comparasion de 2 etiquettes */
		   err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) 	    /* Fonction de chargement d'un element */
{
  err_t noerr = OK ; 
  FILE * fd = NULL ; 
  void * etiquette = NULL ;
 
  /* Ouverture fichier en lecture */
  if( (fd = fopen( nom_fichier , "r" ) ) == NULL )
    {
      fprintf( stderr , "abr_charger: ouverture en lecture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* Destruction de l'arbre si il existe deja */
  if( abr_existe( (*arbre) )  )
    {
      if( (noerr = abr_detruire( arbre ) ) )
	return(noerr) ; 
    }

  /* Creation de l'arbre */
  if( ( (*arbre) = abr_creer( fonction_affectation , 
			      fonction_destruction ,
			      fonction_comparaison ) ) == NULL )      
    return(ERR_DEB_MEMOIRE) ; 


  /* Lecture de la taille de l'arbre */
  int taille = 0 ; 
  if( fscanf( fd , "%d\n" , &taille ) != 1 )
    {
      /* Pas d'element a charger */
      return(OK)  ;
    }

  /* 
   * Chargement 
   */  
  while( ! feof(fd) )
    {
      /* 
       * Lecture 1 ligne :  <etiquette> 
       */
      
      if( (noerr = fonction_chargement( &etiquette , fd ) ) )
	{
	  if( feof(fd) )
	    continue ;
	  else
	    return(noerr) ; 
	}
	 
      /* 
       * Insertion de la valeur dans l'arbre 
       */
     
      if( ( noerr = abr_inserer( (*arbre) , etiquette ) ) )
	return(noerr ) ;
      
      if( ( noerr = fonction_destruction( &etiquette ) ) )
	return(noerr) ;
      
    }

  /* Fermeture */
  fclose(fd) ; 
  
  return(OK) ; 
}

/*
 * Sauvegarde d'un arbre dans un fichier 
 */


static 
err_t abr_sauver_bis( const noeud_t * racine , 
		     FILE * fd  ,						/* File descriptor du fichier de chargement */
		     err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ; 

  /* 
   * Sauvegarde du noeud racine 
   * Creation 1 ligne : <etiquette> 
   */
  
  if( ! noeud_existe( racine ) )
    return(OK) ; 
  
  if( (noerr = fonction_sauvegarde( noeud_etiquette_lire(racine) , 
				    fd ) ) )
    return(noerr) ; 

  fprintf( fd , "\n" ) ; 
      
  /* 
   * Sauvegarde des noeuds dans les sous arbres gauche et droit 
   */
  noeud_t * noeud_fg = noeud_sag_lire(racine) ;
  if( noeud_existe(noeud_fg) )
    {
      if( ( noerr = abr_sauver_bis( noeud_fg ,  fd , fonction_sauvegarde ) ) )
	return(noerr) ; 
    }
  
  noeud_t * noeud_fd = noeud_sad_lire(racine) ;
  if( noeud_existe(noeud_fd) )
    {
      if( ( noerr = abr_sauver_bis( noeud_fd ,  fd , fonction_sauvegarde ) ) )
	return(noerr) ; 
    }

  return(OK) ; 
}

extern 
err_t abr_sauver( const abr_t * arbre  ,						/* Arbre Binaire d'elements a charger */
		 char *  nom_fichier ,						/* Nom du fichier de chargement */
		 err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ; 
  FILE * fd = NULL ; 


  /* Ouverture fichier en ecriture */
  if( (fd = fopen( nom_fichier , "w" ) ) == NULL )
    {
      fprintf( stderr , "abr_sauver: ouverture en ecriture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* test si arbre vide */
  if( !abr_existe( arbre )  )
    return(OK); 

  /* 
   * Sauvegarde
   */  

  /* Taille */
  fprintf( fd , "%d\n" , abr_taille_lire(arbre) ) ; 
  
  /* Elements */
  
  if( ( noerr = abr_sauver_bis(  abr_racine_lire(arbre) , fd  ,fonction_sauvegarde ) ) )
    return(noerr) ; 

  /* Fermeture */
  fclose(fd) ; 
  
  return(OK) ; 
}

/*
 * Recherche du pere d'un noeud dans un arbre 
 */

booleen_t * pere(noeud_t **res,noeud_t * racine,const noeud_t * fils){
	if(racine!=NULL){
		if(racine->gauche==fils||racine->droit==fils){
			*res=racine;
			return VRAI;	
		}
		else{
		
			if(pere(res,racine->gauche,fils))
				return VRAI;
			else if(pere(res,racine->droit,fils))
				return VRAI;
		}
	return FAUX;	
	}
	else
		return FAUX;
}


extern
noeud_t * abr_pere_rechercher( const abr_t * arbre , 
			      const noeud_t * noeud_fils )
{
	noeud_t * res;
	if(pere(&res,arbre->racine,noeud_fils))
		return res;
	else
  		return(NULL) ; 
}


/*
 * Recherche d'un element dans un arbre 
 */

booleen_t recherche(noeud_t ** result , 
			  const noeud_t * racine , 
			  const void * etiquette,
			  int comparer( const void * e1 , const void * e2 )){
	if(racine!=NULL){
		if(comparer(&(racine->etiquette),&etiquette)>0){
			if(recherche(result,racine->gauche,etiquette,comparer))
				return VRAI;
		}
		else if(comparer(&(racine->etiquette),&etiquette)<0){
			if(recherche(result,racine->droit,etiquette,comparer))
				return VRAI;
		}
		else{
			*result=racine;
			return VRAI;
		}
		return FAUX;
	}
	else
		return FAUX;		  

}


extern
booleen_t abr_rechercher( noeud_t ** result , 
			  const abr_t * arbre , 
			  const void * etiquette )
{
  (*result) = NULL ;
  return recherche(result,arbre->racine,etiquette,arbre->comparer);
  
}
