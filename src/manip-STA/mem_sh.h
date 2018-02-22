/*
  Gestion de memoire partagee - creation de la zone
*/
                                                                                 
#ifndef MEM_SH_H__
#define MEM_SH_H__ 

#include <donnees.h>

/*--------------------------------------------------------------------------*/
void erreur(char *prog, char *msg);
/*--------------------------------------------------------------------------*/
void init_memoire(int* shmid);
/*--------------------------------------------------------------------------*/
void libere_memoire(int shmid);
/*--------------------------------------------------------------------------*/
entrees* acces_memoire(int *shmid);

#endif

