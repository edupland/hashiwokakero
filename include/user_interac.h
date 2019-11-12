#ifndef _USER_INTER_
#define _USER_INTER_H_
#include <stdbool.h>


/*
Fonction indiquant combien de ponts peuvent encore être ajoutés en précisant dans quelle direction.
@game g : variable de type jeu.
@int height_add : hauteur maximal de la grille
@int width_add ; largeur maximal de la grille
*/
void brigdes_can_be_add(game g,int height_add,int width_add);

/*
Fonctions modifiant via des pointeurs les différentes variables utiles à la création et suppression de ponts
@int coodonnes_x : pointeur sur une coordonnée en abscice
@int coordonnes_y : pointeur sur une coordonnée en ordonnée
@int direction : pointeur sur un entier correspondant à la direction choisie
*/

void user_choice(int *coordonnes_x,int *coordonnes_y,int *direction,int *dirchoice);

/*
Fonction renvoyant la direction adéquate en fonction d'une variable direction_choix
@int direction_choix : variable entière 
*/

dir choix_direction (int direction_choix);

#endif