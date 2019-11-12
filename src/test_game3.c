#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "test_toolbox.h"



/* Defalult configuration
   2     2     3

   5     1

   3           2
*/

#define EXAMPLE_NB_NODE 7
int vals[EXAMPLE_NB_NODE][3] = {{0,0,3},{0,1,5},{0,2,2},{1,1,1},{1,2,2},{2,0,2},{2,2,3}};

static game default_game () {
    node nodes[EXAMPLE_NB_NODE];
    for (int i = 0 ; i < EXAMPLE_NB_NODE; i++)
      nodes[i] = new_node(vals[i][0],vals[i][1],vals[i][2]);
    game g = new_game(EXAMPLE_NB_NODE, nodes,2,8);
    for (int i = 0 ; i < EXAMPLE_NB_NODE; i++)
      delete_node(nodes[i]);
    return g;
}

bool test_game_over(){
	game g = default_game();
  if(can_add_bridge_dir(g,0,NORTH)){
    add_bridge_dir(g,0,NORTH);
    add_bridge_dir(g,0,NORTH);
    add_bridge_dir(g,0,EAST);
    add_bridge_dir(g,1,NORTH);
    add_bridge_dir(g,1,NORTH);
    add_bridge_dir(g,1,EAST);
  }
  if(can_add_bridge_dir(g,2,NORTH)){
    add_bridge_dir(g,2,NORTH);
    add_bridge_dir(g,6,WEST);
    add_bridge_dir(g,6,WEST);
  }
    bool r = true;
  	dir direction_add;
  	int height_add = 2;
  	int width_add = 2;
  	for(int x= 0;x<=height_add;x++){
    	for(int y = 0;y<=width_add;y++){
      		for(direction_add = NORTH;direction_add<=EAST;direction_add++){ // On parcoure l'enum dir 
        		int number_node = game_get_node_number(g, x, y); // On récupére la valeur du noeud 
        
        		node node_degree = game_node(g,number_node); // Qu'on stocke dans une variable de type node
        
       		 	if(number_node==-1){
          		break;
        		}
        		if(get_degree_dir(g,number_node,direction_add)>=get_required_degree(node_degree))break;
         // On test si le nombre de pont est supérieur à la valeur du noeud
        		if(can_add_bridge_dir(g,number_node,direction_add)){
          		int number_node_voisin = get_neighbour_dir(g,number_node,direction_add);
          		node node_degree_voisin = game_node(g,number_node_voisin);
          		if(get_degree(g,number_node_voisin)>=get_required_degree(node_degree_voisin))break;; // On test si le noeud voisin peut recevoir d'autres ponts 
          		if(direction_add == NORTH)r = false;
          		if(direction_add == WEST)r = false;
          		if(direction_add == SOUTH)r = false;
          		if(direction_add == EAST)r =false;
        		}
    		}
  		}
	}
	delete_game(g);
	return r;

}



bool test_nb_nodes(){
	game g = default_game();
    bool r = true;
    r = r && test_equality_int(7, game_nb_nodes(g), "7");
    delete_game(g);
    return r;

}




int main(int argc, char *argv[]){
	bool result = true;	
	result = result && test_game_over();
	result = result && test_nb_nodes();
	if (result)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}