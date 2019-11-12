#ifndef _INIT_GAME_
#define _INIT_GAME_H_
#include <stdbool.h>


/*
Fonction allouant la tableau de node contenant chaque noeuds du jeu à partir d'un fichier "exemple_jeu.txt"
*/
node *node_init_mem();

/*
Fonction allouant dynamiquement une variable de type jeu.
*/
game game_init_mem();

/*
Fonction permettant de libérer l'espace alloué au tableau de node tab_n dans la fonction node_init_mem()
*/
void free_tab(node *tab_n,int node_val);

#endif
