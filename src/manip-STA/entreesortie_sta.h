#include <time.h>



#define APPG        0        /* Approche gauche */
#define CTR         1        /* Centre*/
#define APPD        2        /* Approche droite */
#define PRESENCE    3        /* Support present */
#define LIM_HOR     4        /* Limite Horizontale*/
#define LIM_VER     5        /* Limite Verticale */
#define API_PC      6        /* API ou PC selectionne */
#define OPERATEUR   7        /* Entree Pause/Arret */

#define V_ACC       0         /* Vitesse Acceleree */
#define HAUT        1         /* Commande haut */
#define BAS         2         /* Commande bas */
#define GAUCHE      3         /* Commande gauche */
#define DROITE      4         /* Commande droite */
#define ALARME      5         /* Alarme */

/* types */
struct S_Entree{
  unsigned char appG;
  unsigned char appD;
  unsigned char ctr;
  unsigned char lim_hor; 
  unsigned char lim_ver;
  unsigned char presence; 
  unsigned char operateur;
  unsigned char fin;
};

struct S_Sortie{
  unsigned char  haut;
  unsigned char bas;
  unsigned char v_acc;
  unsigned char gauche;
  unsigned char droite;
  unsigned char alarme;
};

struct S_Temporisateur{
  int activetempo;  /* Sortie tempo : vraie sur un etat ou une place
                       pdt laquelle la tempo est active */
  int etat;         /* etat de la MEF temporisateur  */
  time_t debuttempo;/* temps initial de la tempo */
};

/* fonctions */
void init_io(void);

unsigned char  entree(unsigned char NoEntree);

void sortie(unsigned char NoSortie,unsigned char  Etat);

int temporisateur(int duree, struct S_Temporisateur *tempo);

/* variable */
extern  short  int idcard;






























