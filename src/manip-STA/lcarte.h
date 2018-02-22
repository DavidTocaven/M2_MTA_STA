#ifndef LCARTE_H
#define LCARTE_H

/*
   Interface lecteur de cartes

   Cablage:
     Pres Carte: B0
     donnees:    B1
     Horloge:    A0
     RAZ:        A1
     Ecrit/Lect   +5V
*/

extern short int carte_ID;

/*----------------------------------------------------------------*/
void initialisations_ports();
/*----------------------------------------------------------------*/
void liberation_ports();
/*----------------------------------------------------------------*/
int carte_inseree(); // renvoie 1 si carte inseree
/*----------------------------------------------------------------*/
void attente_insertion_carte();
/*----------------------------------------------------------------*/
void attente_retrait_carte();
/*----------------------------------------------------------------*/
unsigned short int lecture_numero_carte();


#endif // LCARTE_H
