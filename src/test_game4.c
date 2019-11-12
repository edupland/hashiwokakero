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

bool test_add_bridge_dir(){
  game g = default_game();
  bool r = true;
  for(int i = 0; i < EXAMPLE_NB_NODE; i++){
    if(can_add_bridge_dir(g,i,EAST)){
      add_bridge_dir(g,i,EAST);
      r = r && test_equality_int(1, get_degree_dir(g, i, EAST), "pb with EAST in add_bridge_dir");
      del_bridge_dir(g,i,EAST);
    }
    if(can_add_bridge_dir(g,i,NORTH)){
      add_bridge_dir(g,i,NORTH);
      r = r && test_equality_int(1, get_degree_dir(g, i, NORTH), "pb with NORTH in add_bridge_dir");
      del_bridge_dir(g,i,NORTH);
    }
    if(can_add_bridge_dir(g,i,SOUTH)){
      add_bridge_dir(g,i,SOUTH);
      r = r && test_equality_int(1, get_degree_dir(g, i, SOUTH), "pb with SOUTH in add_bridge_dir");
      del_bridge_dir(g,i,SOUTH);
      }
    if(can_add_bridge_dir(g,i,WEST)){
      add_bridge_dir(g,i,WEST);
      r = r && test_equality_int(1, get_degree_dir(g, i, WEST), "pb with WEST in add_bridge_dir");
      del_bridge_dir(g,i,WEST);
      }
  }
  return r;
}

bool test_delete_game(){
  game g = default_game();
  bool r = true;
  delete_game(g);
  r = r && test_equality_bool(false, g==NULL, "pb with delete_game");
  return r;
}

bool test_copy_game(){
  game g = default_game();
  bool r = true;
  game g2 = copy_game(g);
  for(int i = 0; i < EXAMPLE_NB_NODE; i++){
    r = r && test_equality_int(get_x(game_node(g,i)), get_x(game_node(g2,i)), "pb with x in copy_game");
    r = r && test_equality_int(get_y(game_node(g,i)), get_y(game_node(g2,i)), "pb with y in copy_game");
  }
  return r;
}

int main(int argc, char *argv[]){
  bool result = true;
  result = result && test_add_bridge_dir();
  result = result && test_delete_game();
  result = result && test_copy_game();
  if(result){
    return EXIT_SUCCESS;
  }
  else{
    return EXIT_FAILURE;
  }
}
