#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "node.h"
#include "init_game.h"

void add_bridge(game g,int x, int y, dir direction){ // Fonction d'ajout de pont
   int number_node = game_get_node_number(g, x, y);
   if(number_node == -1)printf("Impossible\n");
   if(can_add_bridge_dir(g, number_node, direction)){
      add_bridge_dir(g, number_node, direction);
   }
   else{
    printf("Impossible d'ajouter un pont !\n");
   }
}

game play_auto(game g, int number_node){
  dir direction_add;
  int i = 0,j = 1; //Variable compteur pour le nombre de voisins que possède un noeud
  int tab_dir[4]; // tableau d'int dans lequel on stocke nos numéros de noeuds de voisins
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
   node node_degree = game_node(g, number_node);

   for(direction_add = NORTH;direction_add<=EAST;direction_add++){ // On compte le nombre de voisins que possède le noeud
    if(can_add_bridge_dir(g,number_node,direction_add)){
      i++;
      tab_dir[j] = get_neighbour_dir(g,number_node,direction_add); // on ajoute le numéro du noeud de son voisin dans le tableau
    }
    j++;
  }


  if (get_required_degree(node_degree) == 8 && get_degree(g2, number_node) == 0){
      printf("coup des 8\n");
      add_bridge(g2, get_x(node_degree), get_y(node_degree), NORTH);
      printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction N\n",get_x(node_degree),get_y(node_degree));
      add_bridge(g2, get_x(node_degree), get_y(node_degree), NORTH);
      printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction N\n",get_x(node_degree),get_y(node_degree));
      add_bridge(g2, get_x(node_degree), get_y(node_degree), WEST);
      printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction W\n",get_x(node_degree),get_y(node_degree));
      add_bridge(g2, get_x(node_degree), get_y(node_degree), WEST);
      printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction W\n",get_x(node_degree),get_y(node_degree));
      add_bridge(g2, get_x(node_degree), get_y(node_degree), SOUTH);
      printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction S\n",get_x(node_degree),get_y(node_degree));
      add_bridge(g2, get_x(node_degree), get_y(node_degree), SOUTH);
      printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction S\n",get_x(node_degree),get_y(node_degree));
      add_bridge(g2, get_x(node_degree), get_y(node_degree), EAST);
      printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction E\n",get_x(node_degree),get_y(node_degree));
      add_bridge(g2, get_x(node_degree), get_y(node_degree), EAST);
      printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction E\n",get_x(node_degree),get_y(node_degree));
  }

  if(get_required_degree(node_degree) == 7 && get_degree(g2, number_node) == 0){
    printf("Coup des 7\n");
    add_bridge(g2, get_x(node_degree), get_y(node_degree), NORTH);
    printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction N\n",get_x(node_degree),get_y(node_degree));
    add_bridge(g2, get_x(node_degree), get_y(node_degree), WEST);
    printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction W\n",get_x(node_degree),get_y(node_degree));
    add_bridge(g2, get_x(node_degree), get_y(node_degree), SOUTH);
    printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction S\n",get_x(node_degree),get_y(node_degree));
    add_bridge(g2, get_x(node_degree), get_y(node_degree), EAST);
    printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction E\n",get_x(node_degree),get_y(node_degree));
  }


  //Just Enough Neighbor Technique : On test si le noeud possède uniquement 2 voisins
  //et si les degrés de ces 2 voisins sont les mêmes que lui, auquel cas on ajoute le nombre de pont requis
  /*if (get_required_degree(node_degree)==4 && i==2 && ((get_required_degree(game_node(g2,tab_dir[1]))==get_required_degree(node_degree) && (get_required_degree(game_node(g2,tab_dir[2])))==get_required_degree(node_degree)))){
    for(direction_add = NORTH;direction_add<=EAST;direction_add++){
      if(can_add_bridge_dir(g, number_node, direction_add)){
      add_bridge_dir(g2, number_node, direction_add);
      add_bridge_dir(g2, number_node, direction_add);
    }
   }
 }*/

  //Si le degré du noeud est 3 et qu'il possède exactement 2 voisins, on ajoute un pont à chacun de ses deux voisins
  if (i==2 && (get_required_degree(node_degree)==3 && get_degree(g2,number_node)==0)){
    for(direction_add = NORTH;direction_add<=EAST;direction_add++){
      if(can_add_bridge_dir(g, number_node, direction_add)){
      add_bridge_dir(g2, number_node, direction_add);
    }
   }
  }

  //One Unsolved Neighbor Technique  : On test si le noeud possède exactement un voisin et si son degré est de 1
  //auquel cas on ajoute immédiatement un pont dans la direction de son voisin
  if(i==1 && get_required_degree(node_degree)==1){
    for(direction_add = NORTH;direction_add<=EAST;direction_add++){
      while(can_add_bridge_dir(g, number_node, direction_add)){
        add_bridge_dir(g2, number_node, direction_add);
      }
    }

  }

      number_node=number_node+1;
      game solution = play_auto(g2,number_node);
      if(solution == NULL){
        return solution;
      }
      else{
        return NULL;
      }
}


game solveur_recursif(game g, int number_node){ // Ce solveur est de type bruteforce et rempli avec un pont chaque fois qu'il peut le faire
   if(number_node == game_nb_nodes(g)){
      if (game_over(g))
      {
        printf("Le jeu est résolu\n");
        return g;
      }
      else{
        printf("Pas de solution trouvé\n");
        exit(EXIT_FAILURE);
      }
   }
   game g2 = g;
   dir direction_add;
   char t_dir[8]={'N','O','S','E'};
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
            add_bridge(g2,get_x(node_degree),get_y(node_degree),NORTH);
            printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction %c\n",get_x(node_degree),get_y(node_degree),t_dir[0]);
          }
          if(direction_add == WEST){
            add_bridge(g2,get_x(node_degree),get_y(node_degree),WEST);
            printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction %c\n",get_x(node_degree),get_y(node_degree),t_dir[1]);
          }
          if(direction_add == SOUTH){
            add_bridge(g2,get_x(node_degree),get_y(node_degree),SOUTH);
            printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction %c\n",get_x(node_degree),get_y(node_degree),t_dir[2]);
          }
          if(direction_add == EAST){
            add_bridge(g2,get_x(node_degree),get_y(node_degree),EAST);
            printf("Un pont a été ajouté en coordonnées (%d,%d) dans la direction %c\n",get_x(node_degree),get_y(node_degree),t_dir[3]);
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

game solveur(game g){
  play_auto(g,0);
  while(!game_over(g)){
    solveur_recursif(g, 0);
  }
    return g;
}



void solution_write(game g,int nb_dir,int nb_max_br, char nom[]){
  FILE* fichier = NULL;
  dir direction_add;

  char solve[8] = ".solved";

  strcat(nom,solve);

  printf("%s\n",nom );

  fichier = fopen(nom, "w");
  int tab_voisins[4] = {0,0,0,0};

  if (fichier != NULL)
    {
      fprintf(fichier,"%d %d %d\n",game_nb_nodes(g),nb_max_br,nb_dir);
      for(int i = 0;i<game_nb_nodes(g);i++){
        int k = 0;
        node node_degree = game_node(g, i);
        for(direction_add = NORTH;direction_add<=EAST;direction_add++){
          int degre_dir = get_degree_dir(g,i,direction_add);
          if(degre_dir==-1)tab_voisins[k]=0;
          else{
            tab_voisins[k]=get_degree_dir(g,i,direction_add);
          }
          k++;
        }
        fprintf(fichier,"%d %d %d %d %d %d %d\n",get_x(node_degree),get_y(node_degree),get_degree(g,i),tab_voisins[0],tab_voisins[1],tab_voisins[2],tab_voisins[3]);
      }
    }
  fclose(fichier);
}


int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage : ./hashi_solve <file_name>\n");
    return EXIT_FAILURE;
  }

  int nb_dir;
   int node_val;
   int nb_max_br;
   int size_max;

   printf("%s\n",argv[1]);


   node *tab_n = node_init_mem(&node_val,&nb_dir,&nb_max_br,&size_max,argv[1]); // On alloue la mémoire pour le tableau de noeuds en appellant la fonction

   game n_game = new_game(node_val,tab_n,nb_max_br,nb_dir);

   if(solveur(n_game))
      solution_write(n_game,nb_dir,nb_max_br,argv[1]);
    free_tab(tab_n, node_val);
    delete_game(n_game);
      return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
