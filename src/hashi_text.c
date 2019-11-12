#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "node.h"
#include "grid_update.h"
#include "init_game.h"
#include "user_interac.h"

#define NODE_VAL 7

// Configuration par défaut :
//2  2  3
//5  1 
//3     2             

//--------------------------------------------------------------------------------------

  
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

void del_bridge(game g,int x,int y,dir direction) // Fonction de suppression de pont
{
   int nodeNumber = game_get_node_number(g, x, y);
   del_bridge_dir(g, nodeNumber, direction);
}


int main(void){
   /*int dirchoice = 0;
   printf("Nombre de directions (4 ou 8) : ");
   scanf("%d", &dirchoice);
   if(dirchoice !=4 && dirchoice != 8){
      fprintf(stderr, "Le nombres de directions doit etre soit 4 soit 8.\n");
      exit(EXIT_FAILURE);
   }
   */
   int nb_dir;
   int node_val;
   int nb_max_br;
   int size_max;
   int answer = 0;
   int coordonnes_x = -1;
   int coordonnes_y = -1;
   int direction_int = -1;
   char file_name[20] = "game_default.txt";
   dir direction = NORTH; // Direction par défaut
   printf("%s\n",file_name);

   
   node *tab_n = node_init_mem(&node_val,&nb_dir,&nb_max_br,&size_max,file_name); // On alloue la mémoire pour le tableau de noeuds en appellant la fonction 
   //game n_game = game_init_mem(); // ON alloue la mémoire pour le jeu
   /*node *tab_n = (node*) malloc(NODE_VAL * sizeof(node)); //On alloue la mémoire pour nos noeuds
   if(tab_n == NULL){
      fprintf(stderr, "NOT ENOUGH MEMORY!\n");
   }*/
   int height = size_max, width = size_max;
   int max_h = 2*height;
   int max_w = 2*width;
   char grid[max_w+1][max_h+1];   

   game n_game = new_game(node_val,tab_n,nb_max_br,nb_dir);
   print_grid_init(n_game,max_w,max_h,grid);

   while(!game_over(n_game)){ // Boucle infinie tant que le jeu n'est pas terminé 
      print_grid(max_w,max_h,grid);
      printf("Choississez une option :\n1.Ajoutez un pont\n2.Supprimer un pont\n3.Aide Jeux\n4.Chargez un jeu\n5.Quittez la partie\n:");
      scanf("%d",&answer);
      switch(answer){
         case 1 : user_choice(&coordonnes_x,&coordonnes_y,&direction_int,&nb_dir);direction = choix_direction(direction_int);add_bridge(n_game,coordonnes_x,coordonnes_y,direction);
            break;
         case 2 : user_choice(&coordonnes_x,&coordonnes_y,&direction_int,&nb_dir);direction = choix_direction(direction_int);del_bridge(n_game,coordonnes_x,coordonnes_y,direction);
            break;
         case 3 : brigdes_can_be_add(n_game,height,width);
            break;
         case 4 :
         {
            delete_game(n_game); 
            free_tab(tab_n,node_val);
            printf("Veuillez entrer un nom de fichier valide : ");
            scanf("%s",file_name);
            tab_n = node_init_mem(&node_val,&nb_dir,&nb_max_br,&size_max,file_name);
            height = size_max, width = size_max;
            max_h = 2*height, max_w = 2*width;
            char grid[max_w+1][max_h+1];
            n_game = new_game(node_val,tab_n,nb_max_br,nb_dir);
            print_grid_init(n_game,max_w,max_h,grid);
            printf("%s\n",file_name);
            break;
         }
         case 5 : delete_game(n_game);free_tab(tab_n,node_val);return EXIT_SUCCESS;
            break;
         default : printf("Veuillez saisir un choix valide");
            break;
      }
      if(answer == 1 || answer == 2){
        print_grid_update(n_game,coordonnes_x,coordonnes_y, direction, max_w, max_h, grid);
        printf("\n");
        printf("\n");
      }
   }

   return 0;
}
