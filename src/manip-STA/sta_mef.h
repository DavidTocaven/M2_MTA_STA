/* prototypes des fonctions sta_mef.h */

void init_bac(void);
int  F_Transport1versSortie(int etat, const struct S_Entree *E, int demande);
void G_Transport1versSortie(int etat, struct S_Sortie *S, int *fin);
int  F_Transport2versSortie(int etat, const struct S_Entree *E, int demande);
void G_Transport2versSortie(int etat,  struct S_Sortie *S, int *fin);

