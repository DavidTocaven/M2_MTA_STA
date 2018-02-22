
/* =======================================================================*/
/*    Squelette de programme pour la mise en oeuvre de MEF synchronisées  */
/*                 Système de Traitement Automatisé                       */
/* =======================================================================*/

/* COMPILATION : */
/*  gcc -Wall -o STA sta-macsed.c -lpci_dask -lsta */

#include <stdio.h>
#include <unistd.h>            // pour sleep()
#include <dask.h>              // pour Release_Card()
#include <signal.h>            // pour déroutement de CTRL C
#include <entreesortie_sta.h>
#include <sta_mef.h>


void Avancer (int, int);
void Reculer (int, int);
void Prendre (void);
void Poser (void);

/* variables externes  */
short int idcard, stop;  

/* declaration globale */
int FinAvancer=0;
int FinReculer=0;
// les entrées
int appG,ctr, appD,presence, lim_hor,lim_ver, operateur;

// les sorties
int v_acc, haut, bas, gauche, droite, alarme;

int main(void)
{

 

  /* Déclarations variables */
int EtatPresent = 1;





  // initialisation des ports 
  init_io();
  //initialisation bac : ramène le système de transport en bas à droite
  //ne doit pas être sur les capteurs en haut ou à gauche 
  init_bac();
printf("init faite \n");       
      sortie(V_ACC,0);
      sortie(HAUT, 0);
      sortie(BAS,0);
      sortie(GAUCHE,0);
      sortie(DROITE,0);
      sortie(ALARME,0);
 
while(1)
    {
      /***********************/ 
      /* Lecture des entrees */
      /***********************/

      appG = entree(APPG);
      ctr = entree(CTR);
      appD = entree(APPD);
      presence = entree(PRESENCE);
      lim_hor = entree(LIM_HOR);
      lim_ver = entree(LIM_VER);
      operateur = entree(OPERATEUR);
    
   
      /* allongement du cycle programme */
      usleep(50);
     
   
 printf ("ctr: %d -- lim hor : %d -- lim vert : %d  \n",ctr,lim_hor, lim_ver);
    }	

      sortie(V_ACC,0);
      sortie(HAUT, 0);
      sortie(BAS,0);
      sortie(GAUCHE,0);
      sortie(DROITE,0);
      sortie(ALARME,0);
  
  return 0;
}



void Prendre (void)
 {printf ("prise d'un objet1\n");
  sortie(HAUT, 1);
  while (entree(LIM_VER));
  printf ("prise d'un objet2\n");
  usleep(10);
  while (!entree(LIM_VER));
  printf ("prise d'un objet3\n");
  sortie(HAUT, 0);
 }
 

void Poser (void)
 {printf ("pose d'un objet\n");
  sortie(BAS,1);
  while (lim_ver);
  while (! lim_ver);
  sortie(BAS,0);
 }
 
 void Avancer (int nb, int start)
 {
  static int Etat = 0;
  static int i = 1;
  switch (Etat)
  {
   case 0 : if (start)
              {
               Etat = 1;
               i=nb;
              }
            break;
   case 1 : if (! ctr) 
               {
                Etat = 2;
               }
             break;             
   case 2 : if (ctr &&(i==1)) 
              {
               Etat = 3;
               FinAvancer=1;
              }
             else if (ctr &&(i!=1))
             {
              Etat=1; i--;
             }
            break;
   case 3 : if (! start) 
               {
                Etat = 0;
                FinAvancer = 0;
               }
             break;
  }

 gauche = ((Etat==1)||(Etat==2));
printf ("EtatAvancer : %d -- gauche : %d\n",Etat, gauche);
}  

void Reculer (int nb, int start)
 {
  static int Etat = 0;
  static int i = 1;
  switch (Etat)
  {
   case 0 : if (start) 
              {
               Etat = 1;
               i=nb;
              }
            break;
   case 1 : if (! ctr) 
               {
                Etat = 2;
               }
             break;             
   case 2 : if (ctr &&(i==1)) 
              {
               Etat = 3;
               FinReculer=1;
              }
             else if (ctr &&(i!=1))
             {
              Etat=1; i--;
             }
            break;
   case 3 : if (! start) 
               {
                Etat = 0;
                FinReculer = 0;
               }
             break;
  }
 droite = ((Etat==1)||(Etat==2));
}                                         














