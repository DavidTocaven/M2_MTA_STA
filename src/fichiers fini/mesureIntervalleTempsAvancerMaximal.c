
/* =======================================================================*/
/*    Squelette de programme pour la mise en oeuvre de MEF synchronisées  */
/*                 Système de Traitement Automatisé                       */
/* =======================================================================*/

/* COMPILATION : gcc -Wall -o STA sta-macsed_rdp.c -lpci_dask -lsta */

/* Exemple qui realise ce RdP (1 jeton initiallement dans p0):

p0 ---------> | --------> p1 ------------> | ------------> p2 ------------> | --
           operateur                   FinAvancer                                                        
                              Avancer(3,1)                  Prendre()                          

----> p3 -------> | --------> p4 --------> | -----> p5 -- | ------------> p6
            [ 5 ; 5 ]                 FinReculer
ne rien faire !          Reculer(2,1)            Poser()            Fin du RdP !   

*/

#include <stdio.h>
#include <unistd.h>            // pour sleep()
#include <dask.h>              // pour Release_Card()
#include <signal.h>            // pour déroutement de CTRL C
#include <entreesortie_sta.h>
#include <sta_mef.h>

// -----------------------------------------------------------------------------
#define NBPLACES 7		
// -----------------------------------------------------------------------------

void Avancer (int, int);
void Reculer (int, int);
void Prendre (void);
void Poser (void);

/* variables externes  */
short int idcard, stop;  

/* declaration globale */
int FinAvancer=0;
int FinReculer=0;

/* etudiant */
time_t 	ti,
	tf;

// les entrées
int appG,ctr, appD,presence, lim_hor,lim_ver, operateur;

// les sorties
int v_acc, haut, bas, gauche, droite, alarme;

int main(void)
{

/* Déclarations variables */

// -----------------------------------------------------------------------------
int p[NBPLACES];	// places "presentes"
int ps[NBPLACES]; 	// places "suivantes"
int i;	
double fintempo;	// variables utilisees pour 		
time_t tempo1;		// la tempo
// -----------------------------------------------------------------------------

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

/* Initialisation variables */	
 
// -----------------------------------------------------------------------------
p[0] = 1;
ps[0] = 1;
for(i=1;i<NBPLACES;i++){
    p[i] = 0;
    ps[i] = 0;
}
fintempo=0;
// -----------------------------------------------------------------------------
ti = 0;
tf = 0;

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
    

// -----------------------------------------------------------------------------
	fintempo = difftime(time(NULL),tempo1);		
// -----------------------------------------------------------------------------
 
     /* allongement du cycle programme */
     // usleep(50);
         
// -----------------------------------------------------------------------------
     	               
    /* blocs F */ 	// Description des transitions possibles
					
	if(p[0]==1){			
		printf("p0 \n");
		if(operateur==1){  // marquage initial, attente d'un appui sur operateur
			ps[0]--;
			ps[1]++;			

		}
	}

	if(p[1]==1){	         
		printf("p1 \n");    // FinAvancer est a 1 lorsque le capteur ctr est a 1
		if(FinAvancer==1){  // et qu'on a parcouru toutes les encoches demandees 
  			ps[1]--;        // Exemple: 3 encoches parcourues si Avancer(2,1)
			ps[2]++;

			Avancer(0,0);	// Remise a zero de la machine a etats definie dans la fonction Avancer

			
		}
	}
		
	if(p[2]==1){	
		printf("p2 \n");
					
		ps[2]--;
		ps[3]++;
	}

	if(p[3]==1){						
		printf("p3 \n");
						
		if(fintempo>=5){  // attente de 5 secondes avant de passer a la place 4   
			ps[3]--; 
			ps[4]++;
		}
	}
		
	if(p[4]==1){	
		printf("p4 \n");	// FinAvancer est a 1 lorsque le capteur ctr est a 1
		if(FinReculer==1){	// et qu'on a parcouru toutes les encoches demandees 
			ps[4]--;		// (exemple : 2 encoches parcourues si on a ecrit Reculer(2,1) )
			ps[5]++;
						
			Reculer(0,0);	// Remise a zero de la machine a etats definie dans la fonction Reculer
		}
	}
		
	if(p[5]==1){	
		printf("p5 \n");
		ps[5]--;
		ps[6]++;
		if (ti == 0)
		{
			//ti = time(NULL);
		}
	}
		
	if(p[6]==1)    // --> fin du Reseau de Petri
		{
			if(tf == 0)
			{
				//tf = time(NULL);
				//printf("P6 : poser : %f \n",difftime(tf,ti));
			}
		}

	/* blocs M */    // Franchissement des transitions

	if(p[3]==0 && ps[3]==1)
	{ 	// du coup, lancement des actions liees au franchissement des transitions    
		tempo1 = time(NULL); 	// (ici, on recupere le "temps actuel" au moment ou on arrive dans la place p3
		
	}							// pour pouvoir ensuite le comparer avec le temps actuel recupere a chaque passage 
								// dans la boucle while -> cf. lecture des entrees et ligne "if(fintempo>=5)")

    for(i=0;i<NBPLACES;i++){ 	// et actualisation des etats presents
        p[i] = ps[i];
	}
// -----------------------------------------------------------------------------
   
      /***************************/
      /* Ecriture des sorties    */
      /***************************/

// -----------------------------------------------------------------------------
     	               
	 /* blocs G */  // gestion des sorties en fonction du marquage mis à jour
	 
	if(p[1]==1){
	if (ti == 0)	
		ti = time(NULL);
        Avancer(8,1);
	
    }
    if(p[2]==1){
    	Prendre();
    }

    if(p[4]==1){
        Reculer(2,1);
    } 
     
	if(p[5]==1){
        Poser();   
   	} 
// -----------------------------------------------------------------------------
  	           
      sortie(V_ACC,0);
     // sortie(HAUT, haut); // actions haut/bas gérées dans les fonctions
     // sortie(BAS,bas);    // Prendre et Poser ci-dessous
      sortie(GAUCHE,gauche);
      sortie(DROITE,droite);
      sortie(ALARME,0);
   
printf ("haut: %d -- bas : %d -- gauche : %d -- droite : %d \n",haut,bas, gauche, droite);
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
  while (entree(LIM_VER));
  while (!entree(LIM_VER));
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
               tf = time(NULL);	
               printf("Avvvvvvvvvvvvvancer : %f \n",difftime(tf,ti));
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














