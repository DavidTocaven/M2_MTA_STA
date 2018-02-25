
/* =======================================================================*/
/*    Squelette de programme pour la mise en oeuvre de MEF synchronis�es  */
/*                 Syst�me de Traitement Automatis�                       */
/* =======================================================================*/

/* COMPILATION : */
/*  gcc -Wall -o STA sta-macsed.c -lpci_dask -lsta */

#include <stdio.h>
#include <unistd.h>            // pour sleep()
#include <dask.h>              // pour Release_Card()
#include <signal.h>            // pour d�routement de CTRL C
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
// les entr�es
int appG,ctr, appD,presence, lim_hor,lim_ver, operateur;

// les sorties
int v_acc, haut, bas, gauche, droite, alarme;

int main(void)
{

 

  /* D�clarations variables */
int EtatPresent = 1;





  // initialisation des ports 
  init_io();
  //initialisation bac : ram�ne le syst�me de transport en bas � droite
  //ne doit pas �tre sur les capteurs en haut ou � gauche 
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









