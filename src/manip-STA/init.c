
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
 while (1) usleep (10);
  return 0;
}









