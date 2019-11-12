#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "node.h"
#include "init_game.h"


// --------------------- Fonctions d'allocation mémoire -------------------

#define NODE_VAL 7

node *node_init_mem(int *node_val,int *nb_dir, int *nb_max_br, int *size_max,char * name){


	FILE* fichier = NULL;
    *size_max = 0;
  	int param[3];
  	int j = 0;
  	int tab_aux[3] = {0,0,0};
 
  	fichier = fopen(name, "r+");

  	if (fichier == NULL){
  		fprintf(stderr, "Ouverture du fichier impossible\n");
  		exit(EXIT_FAILURE);
  	}

  	fscanf(fichier,"%d %d %d",&param[0],&param[1],&param[2]);

  	node *tab_n = (node*) malloc(param[0] * sizeof(node)); //On alloue la mémoire pour nos noeuds 
    if(tab_n == NULL){
      fprintf(stderr, "NOT ENOUGH MEMORY!\n");
    }
    *node_val = param[0];
    *nb_max_br = param[1];       //On enregistre nos parametres 
    *nb_dir = param[2];

    for (int k = 0; k < param[0]; k++)
    {
    	fscanf(fichier,"%d %d %d",&tab_aux[0],&tab_aux[1],&tab_aux[2]);
      if(tab_aux[0] > *size_max || tab_aux[1] > *size_max){
        if(tab_aux[0] > tab_aux[1]){
          *size_max = tab_aux[0];
        }
        else{
            *size_max=tab_aux[1];
          }
      }
      tab_n[j]= new_node(tab_aux[0],tab_aux[1],tab_aux[2]); 
      j++;
      

    }

  fclose(fichier);
  return tab_n;
}

game game_init_mem(){
  game n_game = (game) malloc(sizeof(game));
  if(n_game == NULL){
      fprintf(stderr, "NOT ENOUGH MEMORY!\n");
   }
   return n_game;
}
//----------------------------------------------------------------------------
// ---------------------------------------------------------------------------

void free_tab(node *tab_n,int node_val){
  for(int i=0; i<node_val; ++i)
    free(tab_n[i]);
  free(tab_n);
}