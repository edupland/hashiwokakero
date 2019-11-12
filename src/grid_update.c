#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "node.h"
#include "grid_update.h"



void print_grid_init(cgame g,int max_w,int max_h, char tgrid[max_w+1][max_h+1]){ // Fonction d'affichage de la grille 
   for (int i = 0; i <= max_w; ++i){
      for (int j = 0; j <= max_h; ++j){
	if(i%2 == 0 && j%2 == 0){
	   int number_node = game_get_node_number(g,i/2,j/2);
            if(number_node!=-1){
               node n_value = game_node(g,number_node);
               tgrid[i][j]=get_required_degree(n_value)+'0';
            }
            else
               tgrid[i][j] = ' ';
         }
         else
            tgrid[i][j] = ' ';
      }
   }
}

void print_grid(int max_w, int max_h, char tgrid[max_w+1][max_h+1]){
  printf("\n");
  printf("        "); // Esthéthisme à outrance 
  for (int i = 1; i <= max_w+3; ++i)
  {
    printf("_");
  }
  printf("\n");
  printf("        ");
   for(int j = max_h; j>=0; j--){
      for(int i=0; i<=max_w; i++){
         if(i==0)printf("|");
         printf("%c", tgrid[i][j]);
         if(i==max_w)printf("|");
      }
      printf("\n");
      printf("        ");
   }
   for (int i = 1; i <= max_w+3; ++i)
  {
    printf("-");
  }
   printf("\n");
}

void print_grid_update(cgame c_game, int x, int y, dir direction,int max_w, int max_h,char tgrid[max_w+1][max_h+1]){ // On met la grille à jour
   
  //ON récupère le noeud de départ
  int node_number = game_get_node_number(c_game,x,y);
  int nodeNumber_voisin = get_neighbour_dir(c_game,node_number,direction);
  if (nodeNumber_voisin == -1){
     fprintf(stderr, "Erreur lors de la récupération du noeud voisin.\n");
     exit(EXIT_FAILURE);
  }
  node node_voisin = game_node(c_game,nodeNumber_voisin);
  int numberOfBridge = get_degree_dir(c_game,node_number,direction);
  char pont = ' ';
  //On choisit le caractère adéquate pour le pont
  if (direction == WEST || direction == EAST ){
    switch (numberOfBridge){
    case 0 : pont = ' ';
      break;
    case 1 : pont = '-';
      break;
    case 2 : pont = '=';
      break;
    default : pont = ' ';
    }
  }else if(direction == NORTH || direction == SOUTH){
    switch (numberOfBridge){
    case 0 : pont = ' ';
      break;
    case 1 : pont = '|';
      break;
    case 2 : pont = 'H';
      break;
    default : pont = ' ';
    } 
  }
  else if(direction == NW || direction == SE){
    switch (numberOfBridge){
    case 0 : pont = ' ';
      break;
    case 1 : pont = 92;
      break;
    case 2 : pont = 92;
      break;
    default : pont = ' ';
    } 
  }
  else{
    switch (numberOfBridge){
    case 0 : pont = ' ';
      break;
    case 1 : pont = '/';
      break;
    case 2 : pont = '/';
      break;
    default : pont = ' ';
    } 
  }
  //récupération des coordonnées du noeud voisin
  int x_voisin = get_x(node_voisin);
  int y_voisin = get_y(node_voisin);
  int xMax = 0,xMin = 0,yMin = 0,yMax = 0;
  //si le pont est horizontal = ouest ou est
  if(direction == EAST || direction == WEST ){
    if ( x > x_voisin ){
      xMax = x*max_w/2;
      xMin = x_voisin*max_w/2;
    }else{
      xMax = x_voisin*max_w/2;
      xMin = x*max_w/2;
    }
    for ( int i = xMin+1 ; i < xMax ; i++){
      tgrid[i][y*max_h/2] = pont;
    }
  }else if(direction == NORTH || direction == SOUTH){
    // si le pont est vertical = Nord ou sud
    if ( y > y_voisin ){
      yMax = y*max_h/2;
      yMin = y_voisin*max_h/2;
    }else{
      yMax = y_voisin*max_h/2;
      yMin = y*max_h/2;
    }
    for ( int i = yMin+1 ; i < yMax ; i++){
      tgrid[x*max_w/2][i] = pont;
    }
  }
  else{
    // si le pont est en diagonale
    if ( y > y_voisin ){
      yMax = y*max_h/2;
      yMin = y_voisin*max_h/2;
    }else{
      yMax = y_voisin*max_h/2;
      yMin = y*max_h/2;
    }
    if ( x > x_voisin ){
      xMax = x*max_w/2;
      xMin = x_voisin*max_w/2;
    }else{
      xMax = x_voisin*max_w/2;
      xMin = x*max_w/2;
    }

    for ( int i = yMin+1,j=xMin+1 ; i < yMax && j < xMax; i++,j++){
      tgrid[j][i] = pont;
    }
  }
}
