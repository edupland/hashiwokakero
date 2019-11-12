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

bool test_del_bridge_dir(){
	game g = default_game();
	bool r = true;
	if(can_add_bridge_dir(g, 0, NORTH))
		add_bridge_dir(g, 0, NORTH);

	del_bridge_dir(g, 0, NORTH);
	r = r && test_equality_int(0, get_degree_dir(g, 0, NORTH), "pb with del_bridge_dir.");
	return r;
}

bool test_get_degree_dir(){
	game g = default_game();
	if (can_add_bridge_dir(g, 0, NORTH)){
		add_bridge_dir(g, 0, NORTH);
		del_bridge_dir(g, 0,NORTH);
		add_bridge_dir(g, 0, NORTH);
		add_bridge_dir(g, 0, NORTH);
	}
	if (can_add_bridge_dir(g, 1, EAST))
		add_bridge_dir(g, 1, EAST);
	bool r = true;
	r = r && test_equality_int(2, get_degree_dir(g, 0, NORTH), "pb with degree at node 0.");
	r = r && test_equality_int(1, get_degree_dir(g, 1, EAST), "pb with degree at node 1.");
	delete_game(g);
	return r;
}

bool test_get_degree(){
	game g = default_game();
	if(can_add_bridge_dir(g, 0, NORTH) && can_add_bridge_dir(g, 0, EAST)){
		add_bridge_dir(g, 0, NORTH);
		add_bridge_dir(g, 0, NORTH);
		add_bridge_dir(g, 0, EAST);
	}
	bool r = true;
	r = r && test_equality_int(3, get_degree(g, 0), "pb with get_degree at node 0.");
	return r;
}

int main(int argc, char *argv[]){
	bool result = true;	
	result = result && test_get_degree_dir();
	result = result && test_del_bridge_dir();
	result = result && test_get_degree();
	if (result)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}