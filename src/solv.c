#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "node.h"





game solveur_recursif(game g, int number_node){

   if(number_node == game_nb_nodes(g)){
      if (game_over(g))
      {
        printf("Le jeu est résolu\n");
        return copy_game(g);
      }
      else{
        return NULL;
      }
   }
   game g2 = g;
   dir direction_add;
   char t_dir[4]={'N','O','S','E'};
  /*while(!game_over(g)){*/
      for(direction_add = NORTH;direction_add<=EAST;direction_add++){ // On parcoure l'enum dir 
        //int number_node = game_get_node_number(g, x, y); // On récupérer la valeur du noeud 
        
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
          if(direction_add == NORTH){
            while(can_add_bridge_dir(g,number_node,direction_add)){
              add_bridge(g2,get_x(node_degree),get_y(node_degree),NORTH);
              printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction %c\n",get_x(node_degree),get_y(node_degree),t_dir[0]);
            }
          }
          if(direction_add == WEST){
            while(can_add_bridge_dir(g,number_node,direction_add)){
              add_bridge(g2,get_x(node_degree),get_y(node_degree),WEST);
              printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction %c\n",get_x(node_degree),get_y(node_degree),t_dir[1]);
            }
          }
          if(direction_add == SOUTH){
            while(can_add_bridge_dir(g,number_node,direction_add)){
              add_bridge(g2,get_x(node_degree),get_y(node_degree),SOUTH);
              printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction %c\n",get_x(node_degree),get_y(node_degree),t_dir[2]);
            }
          }
          if(direction_add == EAST){
            while(can_add_bridge_dir(g,number_node,direction_add)){

              add_bridge(g2,get_x(node_degree),get_y(node_degree),EAST);
              printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction %c\n",get_x(node_degree),get_y(node_degree),t_dir[3]);
          }
        }
      }
    }
      number_node=number_node+1;
      game solution = solveur_recursif(g2,number_node);
      if(solution == NULL){
        return solution;
      }
      else{
        return NULL;
      }
}
//ajouter pont dans une direction puis tester en commençant par chacune différente
int *posibilitie(game g,int number_node){
	dir direction_add;
	int i = 0;
	int *tab_pob;
	int number_of_bridge;
	for(direction_add = NORTH;direction_add<=EAST;direction_add++){
		if(can_add_bridge_dir(g,number_node,direction_add)){
			node node_degree = game_node(g,number_node);
			int number_node_voisin = get_neighbour_dir(g,number_node,direction_add);
        	node node_degree_voisin = game_node(g,number_node_voisin);
        	number_of_bridge = get_degree(node_degree) - get_degree(node_degree_voisin);
        	if(number_of_bridge) < 0{
        		number_of_bridge = get_degree(node_degree_voisin) - get_degree(node_degree);	
        	}
			tab_pob[i]=number_of_bridge;
			i++;
		}
		else
		{
			tab_pob[i]=0;
			i++;
		}
		
	}
	return tab_pob;

}

void delete_nodes(game g,node node_degree){
	dir direction_add;
	for(direction_add = NORTH;direction_add<=EAST;direction_add++){
		del_bridge(g,get_x(node_degree),get_y(node_degree),direction_add);
	}
}

game solveur(game g){
   return solveur_recursif(g, 0);
}
