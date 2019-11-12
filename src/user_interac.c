#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "node.h"

void brigdes_can_be_add(game g,int height_add,int width_add){ // Fonction d'aide de l'utilisateur
  printf("----------------------------------------------\n");
  dir direction_add;
  char t_dir[4]={'N','O','S','E'};
  /*while(!game_over(g)){*/
  for(int x= 0;x<=height_add;x++){
    for(int y = 0;y<=width_add;y++){
      for(direction_add = NORTH;direction_add<=EAST;direction_add++){ // On parcoure l'enum dir 
        int number_node = game_get_node_number(g, x, y); // On récupérer la valeur du noeud 
        
        node node_degree = game_node(g,number_node); // Qu'on stocke dans une variable de type node
        
        if(number_node==-1){
          break;
        }
        if(get_degree_dir(g,number_node,direction_add)>=get_required_degree(node_degree))break;
        if(get_degree(g,number_node)>=get_required_degree(node_degree))break;
         // On test si le nombre de pont est supérieur à la valeur du noeud
        if(can_add_bridge_dir(g,number_node,direction_add)){
          int number_node_voisin = get_neighbour_dir(g,number_node,direction_add);
          node node_degree_voisin = game_node(g,number_node_voisin);
          if(get_degree(g,number_node_voisin)>=get_required_degree(node_degree_voisin))break;; // On test si le noeud voisin peut recevoir d'autres ponts 
          if(direction_add == NORTH)printf("Un pont peut être ajouté en coordonnées (%d,%d) dans la direction %c\n",x,y,t_dir[0]);
          if(direction_add == WEST)printf("Un pont peut être ajouté en coordonnées (%d,%d) dans la direction %c\n",x,y,t_dir[1]);
          if(direction_add == SOUTH)printf("Un pont peut être ajouté en coordonnées (%d,%d) dans la direction %c\n",x,y,t_dir[2]);
          if(direction_add == EAST)printf("Un pont peut être ajouté en coordonnées (%d,%d) dans la direction %c\n",x,y,t_dir[3]);
        }
      }
    }
  }
//}
}

// --------------------------- Interaction avec l'utilisateur -----------------------

void user_choice(int *coordonnes_x,int *coordonnes_y,int *direction, int *dirchoice){
  *coordonnes_x = -1, *coordonnes_y=-1; *direction = -1;
  while(*coordonnes_x == -1 && *coordonnes_y == -1){
   printf("Veuillez choisir les coordonnées de l'île :\n");
   printf("x:");
   scanf("%d",coordonnes_x);
   printf("\n");
   printf("y:");
   scanf("%d",coordonnes_y);
  }
  if (*dirchoice == 4){
    while((*direction != 1) && (*direction != 2) && (*direction != 3) && (*direction != 4))
    {
        printf("Veuillez choisir une direction :\n1.NORD\n2.OUEST\n3.SUD\n4.EST\n:");
        scanf("%d", direction);
      }
    }
  else{
    while((*direction != 1) && (*direction != 2) && (*direction != 3) && (*direction != 4)  && (*direction != 5)  && (*direction != 6)  && (*direction != 7)  && (*direction != 8)){
        printf("Veuillez choisir une direction :\n1.NORD\n2.OUEST\n3.SUD\n4.EST\n5.Nord-Ouest\n6.Nord-Est\n7.Sud-Ouest\n8.Sud-Est:");
        scanf("%d",direction);
    }
  }
    printf("\n");

}

dir choix_direction (int direction_choix) {
   switch (direction_choix) {
      case 1 : return NORTH;
      case 2 : return WEST;
      case 3 : return SOUTH;
      case 4 : return EAST;
      case 5 : return NW;
      case 6 : return NE;
      case 7 : return SW;
      case 8 : return SE;
      default : exit(EXIT_FAILURE);
  }
}

//--------------------------------------------------------------------------------------
