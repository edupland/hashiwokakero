#ifndef _GRID_UPDATE_
#define _GRID_UPDATE_H_
#include <stdbool.h>


/*Fonction d'initialisation de la grille d'affichage du jeu
@cgame g : variable de type jeu issue de game.c
@ int max_w : largeur maximal de la grille
@int max_h : hauteur maximale de la grille
@ char tgrid : tableau à deux dimensions 
*/
void print_grid_init(cgame g,int max_w,int max_h, char tgrid[max_w+1][max_h+1]);

/*Fonction permettant l'affichage dans la console de la grille précedemment initalisé
@ int max_w : largeur max de la grille
@ int max_h : hauteur maximal de la grille
@char tgrid : tableau à deux dimesions
*/
void print_grid(int max_w, int max_h, char tgrid[max_w+1][max_h+1]);

/*Fonctions permettant d'actualiser la grille à chaque ajout ou suppression de ponts 
@cgame g : variable de type jeu issue de game.c
@int x : coordonnée en absicce du pont ajouté ou supprimé
@int y : coordonnée en ordonnée du pont ajouté ou supprimé
@dir direction : variable enum correspondant à la direction du pont 
@ int max_w : largeur maximal de la grille
@int max_h : hauteur maximale de la grille
@ char tgrid : tableau à deux dimensions 
*/
void print_grid_update(cgame c_game, int x, int y, dir direction,int max_w, int max_h,char tgrid[max_w+1][max_h+1]);

#endif

