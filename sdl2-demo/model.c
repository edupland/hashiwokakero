#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>  // required to load transparent texture from PNG
#include <SDL2/SDL_ttf.h>    // required to use TTF fonts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "model.h"
#include "game.h"
#include "node.h"
#include "init_game.h"

/* **************************************************************** */

#define FONT "Police/cs_regular.ttf"
#define FONT1 "Police/FLATS.ttf"
#define FONTSIZE 36
#define SIZE 65
#define BACKGROUND "fond2.jpg"
#define CURSEUR "curseur.png"
#define FLECHE "images.png"
#define PONTSIMPLEH "pontsimple.png"
#define PONTDOUBLEH "doublepont.png"
#define PONTSIMPLEV "pontsimplev.png"
#define PONTDOUBLEV "pontdoublev.png"

/* **************************************************************** */

//enum { ECRAN1, ECRAN2, ECRAN3, ECRAN4};

struct Env_t {

  /* PUT YOUR VARIABLES HERE */

  SDL_Texture * background;
  SDL_Texture * titre;
  SDL_Texture * nouv;
  SDL_Texture * nouvbis;
  SDL_Texture * nouvor;
  SDL_Texture * regle;
  SDL_Texture * regletitre;
  SDL_Texture * reglebis;
  SDL_Texture * regleor;
  SDL_Texture * regle1;
  SDL_Texture * regle2;
  SDL_Texture * regle3;
  SDL_Texture * regle3bis;
  SDL_Texture * regle4;
  SDL_Texture * regle4bis;
  SDL_Texture * quitter;
  SDL_Texture * quitterbis;
  SDL_Texture * quitteror;
  SDL_Texture * fleche;
  SDL_Texture * flechebis;
  SDL_Texture * flecheor;
  SDL_Texture * choix;
  SDL_Texture * choixbis;
  SDL_Texture * easy;
  SDL_Texture * easybis;
  SDL_Texture * easyor;
  SDL_Texture * medium;
  SDL_Texture * mediumbis;
  SDL_Texture * mediumor;
  SDL_Texture * hard;
  SDL_Texture * hardbis;
  SDL_Texture * hardor;
  SDL_Texture * help;
  SDL_Texture * helpbis;
  SDL_Texture * helpor;
  SDL_Texture * sol;
  SDL_Texture * solbis;
  SDL_Texture * solor;
  SDL_Texture * home;
  SDL_Texture * homebis;
  SDL_Texture * homeor;
  SDL_Texture * gagner;
  SDL_Texture * tmp;
  SDL_Texture * degree[9];
  SDL_Texture * degreeor[9];
  SDL_Texture * nodes[500];
  SDL_Texture * un;
  SDL_Texture * deux;
  SDL_Texture * trois;
  SDL_Texture * quatre;
  SDL_Texture * cinq;
  SDL_Texture * six;
  SDL_Texture * sept;
  SDL_Texture * huit;
  SDL_Texture * pontsimpleh;
  SDL_Texture * pontdoubleh;
  SDL_Texture * pontsimplev;
  SDL_Texture * pontdoublev;
  SDL_Rect * coordonnes[500][4]; //Coordonnées de chaque nodes
  game * n_game; //Le game provenant de new_game
  node * tab_n; //Tableau de nodes
  int * help_count; // Savoir si l'utilisateur a déjà utilisé l'aide
  int * node_num; //Numéro de node
  int * x_max;
  int * y_max;
  int * nodes_to_add[2]; //Numéro des nodes auxquelles on ajoute un pont
  int * lock; // variable pour identifier si deux noeuds ont été sélectionnés
  int * load; // variable de type int indiquant si la game a été init
  bool * solved;

  //SDL_Texture * jeu;

  int ecran;

};


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
        printf("Pas de solution trouvé\n")
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

game solveur(game *g){
  play_auto(g,0);
  while(!game_over(g)){
    solveur_recursif(g, 0);
  }
    return g;
}

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{
  Env * env = malloc(sizeof(struct Env_t));
  env->load = 0;
  env->lock=0;
  env->ecran = 0;
  env->x_max=0;
  env->y_max=0;
  env->help_count = 0;
  env->solved = false;

  if(argc==2){ // Si on passe le nom d'un jeu en argument
    init_game_SDL(env,argv[1]);
  }

  PRINT("Cliquez sur Jouer avec la souris\nOu appuyez sur entrée\n");

  /* PUT YOUR CODE HERE TO INIT TEXTURES, ... */

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);





  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  env->pontsimpleh = IMG_LoadTexture(ren, PONTSIMPLEH);
  if(!env->pontsimpleh) ERROR("IMG_LoadTexture: %s\n", PONTSIMPLEH);

  env->pontdoubleh = IMG_LoadTexture(ren, PONTDOUBLEH);
  if(!env->pontdoubleh) ERROR("IMG_LoadTexture: %s\n", PONTDOUBLEH);

  env->pontsimplev = IMG_LoadTexture(ren, PONTSIMPLEV);
  if(!env->pontsimplev) ERROR("IMG_LoadTexture: %s\n", PONTSIMPLEV);

  env->pontdoublev = IMG_LoadTexture(ren, PONTDOUBLEV);
  if(!env->pontdoublev) ERROR("IMG_LoadTexture: %s\n", PONTDOUBLEV);

  SDL_Color blanc = {200,200,200,255};
  SDL_Color orange = {167,103,38,255};

  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s", FONT);
  TTF_Font * font1 = TTF_OpenFont(FONT, 30);
  if(!font1) ERROR("TTF_OpenFont: %s", FONT);
  TTF_Font * font2 = TTF_OpenFont(FONT, SIZE);
  if(!font2) ERROR("TTF_OpenFont: %s", FONT);
  TTF_Font * fontor = TTF_OpenFont(FONT, FONTSIZE);
  if(!fontor) ERROR("TTF_OpenFont: %s", FONT);
  TTF_Font * fonttitre = TTF_OpenFont(FONT1, SIZE);
  if(!fonttitre) ERROR("TTF_OpenFont: %s", FONT1);

  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  TTF_SetFontStyle(font2, TTF_STYLE_NORMAL);
  TTF_SetFontStyle(font1, TTF_STYLE_NORMAL);
  TTF_SetFontStyle(fontor, TTF_STYLE_ITALIC);
  TTF_SetFontStyle(fonttitre, TTF_STYLE_NORMAL);

  SDL_Surface ** chiffre = malloc(9*sizeof(SDL_Surface)); // Déclaration dans un tableau des chiffres
  int j = 0;
  char snum[9];
  for(int i = 0;i<=8;i++){
    sprintf(snum,"%d",j);
    chiffre[i]=TTF_RenderText_Blended(font, snum, blanc);
    j = j+1;
  }

  SDL_Surface ** chiffre_or = malloc(9*sizeof(SDL_Surface)); // Déclaration dans un tableau des chiffres
  int k = 0;
  char snum_or[9];
  for(int i = 0;i<=8;i++){
    sprintf(snum_or,"%d",k);
    chiffre_or[i]=TTF_RenderText_Blended(font, snum_or, orange);
    k = k+1;
  }

  SDL_Surface * surftitre =TTF_RenderText_Blended(fonttitre, "HASHIWOKAKERO", blanc);
  SDL_Surface * surf1 = TTF_RenderText_Blended(font, "Nouvelle Partie", blanc);
  SDL_Surface * surf3 = TTF_RenderUTF8_Blended(font, "Règles", blanc);
  SDL_Surface * surf4 = TTF_RenderText_Blended(font, "Quitter", blanc);
  SDL_Surface * surf5 = TTF_RenderText_Blended(fonttitre, "CHOISIR LE", blanc);
  SDL_Surface * surf5bis = TTF_RenderText_Blended(fonttitre, "NIVEAU", blanc);
  SDL_Surface * surf6 = TTF_RenderText_Blended(font, "Facile", blanc);
  SDL_Surface * surf7 = TTF_RenderText_Blended(font, "Moyen", blanc);
  SDL_Surface * surf8 = TTF_RenderText_Blended(font, "Difficile", blanc);
  SDL_Surface * surf9 = TTF_RenderText_Blended(font2, "<", blanc);
  SDL_Surface * surf10 = TTF_RenderText_Blended(font, "Aide", blanc);
  SDL_Surface * surf11 = TTF_RenderText_Blended(font, "Solution", blanc);
  SDL_Surface * surf12 = TTF_RenderText_Blended(font, "Accueil", blanc);
  SDL_Surface * surf13 = TTF_RenderUTF8_Blended(font1, "Tout pont débute et finit sur une île", blanc);
  SDL_Surface * surf14 = TTF_RenderText_Blended(font1, "Aucun pont ne peut en croiser un autre", blanc);
  SDL_Surface * surf15 = TTF_RenderUTF8_Blended(font1, "Le nombre de ponts qui passent est indiqué", blanc);
  SDL_Surface * surf15bis = TTF_RenderUTF8_Blended(font1, "sur l'île", blanc);
  SDL_Surface * surf16 = TTF_RenderUTF8_Blended(font1, "Toutes les îles doivent être reliées entre", blanc);
  SDL_Surface * surf16bis = TTF_RenderUTF8_Blended(font1, "elles", blanc);
  SDL_Surface * surf17 = TTF_RenderUTF8_Blended(fonttitre, "REGLES", blanc);
  SDL_Surface * surf18 = TTF_RenderUTF8_Blended(font, "Vous avez gagné", blanc);

  SDL_Surface * surf1or = TTF_RenderText_Blended(fontor, "Nouvelle Partie", orange);
  SDL_Surface * surf3or = TTF_RenderUTF8_Blended(fontor, "Règles", orange);
  SDL_Surface * surf4or = TTF_RenderText_Blended(fontor, "Quitter", orange);
  SDL_Surface * surf6or = TTF_RenderText_Blended(fontor, "Facile", orange);
  SDL_Surface * surf7or = TTF_RenderText_Blended(fontor, "Moyen", orange);
  SDL_Surface * surf8or = TTF_RenderText_Blended(fontor, "Difficile", orange);
  SDL_Surface * surf9or = TTF_RenderText_Blended(font2, "<", orange);
  SDL_Surface * surf10or = TTF_RenderText_Blended(fontor, "Aide", orange);
  SDL_Surface * surf11or = TTF_RenderText_Blended(fontor, "Solution", orange);
  SDL_Surface * surf12or = TTF_RenderText_Blended(fontor, "Accueil", orange);

  /* SDL_Surface * jeu = SDL_LoadBMP("hashi_texte.c"); */

  /* env->jeu = SDL_CreateTextureFromSurface(ren, jeu); */

  /*Déclaration des chiffres des îlots*/

  env->un = SDL_CreateTextureFromSurface(ren,chiffre[0]);
  env->deux = SDL_CreateTextureFromSurface(ren,chiffre[1]);
  env->trois = SDL_CreateTextureFromSurface(ren,chiffre[2]);
  env->quatre = SDL_CreateTextureFromSurface(ren,chiffre[3]);
  env->cinq = SDL_CreateTextureFromSurface(ren,chiffre[4]);
  env->six = SDL_CreateTextureFromSurface(ren,chiffre[5]);
  env->sept = SDL_CreateTextureFromSurface(ren,chiffre[6]);
  env->huit = SDL_CreateTextureFromSurface(ren,chiffre[7]);


  for(int i = 0;i<=8;i++){
    env->degree[i] = SDL_CreateTextureFromSurface(ren,chiffre[i]);
  }

  for(int i = 0;i<=8;i++){
    env->degreeor[i] = SDL_CreateTextureFromSurface(ren,chiffre_or[i]);
  }

  env->titre = SDL_CreateTextureFromSurface(ren, surftitre);
  env->nouv = SDL_CreateTextureFromSurface(ren, surf1);
  env->regle = SDL_CreateTextureFromSurface(ren, surf3);
  env->quitter = SDL_CreateTextureFromSurface(ren, surf4);
  env->choix = SDL_CreateTextureFromSurface(ren, surf5);
  env->choixbis = SDL_CreateTextureFromSurface(ren, surf5bis);
  env->easy = SDL_CreateTextureFromSurface(ren, surf6);
  env->medium = SDL_CreateTextureFromSurface(ren, surf7);
  env->hard = SDL_CreateTextureFromSurface(ren, surf8);
  env->fleche = SDL_CreateTextureFromSurface(ren, surf9);
  env->help = SDL_CreateTextureFromSurface(ren, surf10);
  env->sol = SDL_CreateTextureFromSurface(ren, surf11);
  env->home = SDL_CreateTextureFromSurface(ren, surf12);
  env->regle1 = SDL_CreateTextureFromSurface(ren, surf13);
  env->regle2 = SDL_CreateTextureFromSurface(ren, surf14);
  env->regle3 = SDL_CreateTextureFromSurface(ren, surf15);
  env->regle3bis = SDL_CreateTextureFromSurface(ren, surf15bis);
  env->regle4 = SDL_CreateTextureFromSurface(ren, surf16);
  env->regle4bis = SDL_CreateTextureFromSurface(ren, surf16bis);
  env->regletitre = SDL_CreateTextureFromSurface(ren, surf17);
  env->gagner = SDL_CreateTextureFromSurface(ren, surf18);

  env->nouvbis = SDL_CreateTextureFromSurface(ren, surf1);
  env->reglebis = SDL_CreateTextureFromSurface(ren, surf3);
  env->quitterbis = SDL_CreateTextureFromSurface(ren, surf4);
  env->easybis = SDL_CreateTextureFromSurface(ren, surf6);
  env->mediumbis = SDL_CreateTextureFromSurface(ren, surf7);
  env->hardbis = SDL_CreateTextureFromSurface(ren, surf8);
  env->flechebis = SDL_CreateTextureFromSurface(ren, surf9);
  env->helpbis = SDL_CreateTextureFromSurface(ren, surf10);
  env->solbis = SDL_CreateTextureFromSurface(ren, surf11);
  env->homebis = SDL_CreateTextureFromSurface(ren, surf12);

  env->nouvor = SDL_CreateTextureFromSurface(ren, surf1or);
  env->regleor = SDL_CreateTextureFromSurface(ren, surf3or);
  env->quitteror = SDL_CreateTextureFromSurface(ren, surf4or);
  env->easyor = SDL_CreateTextureFromSurface(ren, surf6or);
  env->mediumor = SDL_CreateTextureFromSurface(ren, surf7or);
  env->hardor = SDL_CreateTextureFromSurface(ren, surf8or);
  env->flecheor = SDL_CreateTextureFromSurface(ren, surf9or);
  env->helpor = SDL_CreateTextureFromSurface(ren, surf10or);
  env->solor = SDL_CreateTextureFromSurface(ren, surf11or);
  env->homeor = SDL_CreateTextureFromSurface(ren, surf12or);

  //Freesurface des chiffres
  for(int i=0;i<9;i++){
    SDL_FreeSurface(chiffre[i]);
  }
  for(int i=0;i<9;i++){
    SDL_FreeSurface(chiffre_or[i]);
  }

  SDL_FreeSurface(surftitre);
  SDL_FreeSurface(surf1);
  SDL_FreeSurface(surf3);
  SDL_FreeSurface(surf4);
  SDL_FreeSurface(surf5);
  SDL_FreeSurface(surf5bis);
  SDL_FreeSurface(surf6);
  SDL_FreeSurface(surf7);
  SDL_FreeSurface(surf8);
  SDL_FreeSurface(surf9);
  SDL_FreeSurface(surf10);
  SDL_FreeSurface(surf11);
  SDL_FreeSurface(surf12);
  SDL_FreeSurface(surf13);
  SDL_FreeSurface(surf14);
  SDL_FreeSurface(surf15);
  SDL_FreeSurface(surf15bis);
  SDL_FreeSurface(surf16);
  SDL_FreeSurface(surf16bis);
  SDL_FreeSurface(surf17);
  SDL_FreeSurface(surf18);

  //SDL_FreeSurface(jeu);

  SDL_FreeSurface(surf1or);
  SDL_FreeSurface(surf3or);
  SDL_FreeSurface(surf4or);
  SDL_FreeSurface(surf6or);
  SDL_FreeSurface(surf7or);
  SDL_FreeSurface(surf8or);
  SDL_FreeSurface(surf9or);
  SDL_FreeSurface(surf10or);
  SDL_FreeSurface(surf11or);
  SDL_FreeSurface(surf12or);

  free(chiffre);
  free(chiffre_or);



  return env;
}

/* **************************************************************** */

void render_menu_souris(SDL_Window* win, SDL_Renderer* ren, Env * env){

  SDL_Rect rect;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  /*POSITION TITRE*/
  SDL_QueryTexture(env->titre, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = h/4 - rect.h/2;
  SDL_RenderCopy(ren, env->titre, NULL, &rect);

  /*POSITION JOUER*/
  SDL_QueryTexture(env->nouv, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = 8*h/16 - rect.h/2;
  SDL_RenderCopy(ren, env->nouv, NULL, &rect);

  /*POSITION SOLUTION*/
  SDL_QueryTexture(env->regle, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = 10*h/16 - rect.h/2;
  SDL_RenderCopy(ren, env->regle, NULL, &rect);

  /*POSITION QUITTER*/
  SDL_QueryTexture(env->quitter, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = 12*h/16 - rect.h/2;
  SDL_RenderCopy(ren, env->quitter, NULL, &rect);
}


void render_niveau_souris(SDL_Window* win, SDL_Renderer* ren, Env * env){

  SDL_Rect rect;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  SDL_QueryTexture(env->choix, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 7*h/32 - rect.h/2;
  SDL_RenderCopy(ren, env->choix, NULL, &rect);

  SDL_QueryTexture(env->choixbis, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = 9*h/32 - rect.h/2;
  SDL_RenderCopy(ren, env->choixbis, NULL, &rect);

  SDL_QueryTexture(env->easy, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 7*h/16 - rect.h/2;
  SDL_RenderCopy(ren, env->easy, NULL, &rect);

  SDL_QueryTexture(env->medium, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 9*h/16 - rect.h/2;
  SDL_RenderCopy(ren, env->medium, NULL, &rect);

  SDL_QueryTexture(env->hard, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 11*h/16 - rect.h/2;
  SDL_RenderCopy(ren, env->hard, NULL, &rect);

  SDL_QueryTexture(env->fleche, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 13*h/16 - rect.h/2;
  SDL_RenderCopy(ren, env->fleche, NULL, &rect);
}


void render_regle_souris(SDL_Window* win, SDL_Renderer* ren, Env * env){

  SDL_Rect rect;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  SDL_SetRenderDrawColor(ren, 255,255,255,255);
  SDL_Rect haut;
  haut.x = 40;
  haut.y = 11*h/32;
  haut.w = w-80;
  haut.h = 1;
  SDL_RenderFillRect(ren, &haut);

  SDL_Rect bas;
  bas.x = 40;
  bas.y = 26*h/32;
  bas.w = w-80;
  bas.h = 1;
  SDL_RenderFillRect(ren, &bas);

  SDL_Rect gauche;
  gauche.x = 40;
  gauche.y = 11*h/32;
  gauche.w = 1;
  gauche.h = 15*h/32;
  SDL_RenderFillRect(ren, &gauche);

  SDL_Rect droite;
  droite.x = w-40;
  droite.y = 11*h/32;
  droite.w = 1;
  droite.h = 15*h/32;
  SDL_RenderFillRect(ren, &droite);

  SDL_QueryTexture(env->regletitre, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = h/6 - rect.h/2;
  SDL_RenderCopy(ren, env->regletitre, NULL, &rect);

  SDL_QueryTexture(env->regle1, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 12*h/32 - rect.h/2;
  SDL_RenderCopy(ren, env->regle1, NULL, &rect);

  SDL_QueryTexture(env->regle2, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 16*h/32 - rect.h/2;
  SDL_RenderCopy(ren, env->regle2, NULL, &rect);

  SDL_QueryTexture(env->regle3, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 20*h/32 - rect.h/2;
  SDL_RenderCopy(ren, env->regle3, NULL, &rect);

  SDL_QueryTexture(env->regle3bis, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 21*h/32 - rect.h/2;
  SDL_RenderCopy(ren, env->regle3bis, NULL, &rect);

  SDL_QueryTexture(env->regle4, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 24*h/32 - rect.h/2;
  SDL_RenderCopy(ren, env->regle4, NULL, &rect);

  SDL_QueryTexture(env->regle4bis, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2- rect.w/2; rect.y = 25*h/32 - rect.h/2;
  SDL_RenderCopy(ren, env->regle4bis, NULL, &rect);

  SDL_QueryTexture(env->fleche, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/33 - rect.w/2; rect.y = 63*h/66 - rect.h/2;
  SDL_RenderCopy(ren, env->fleche, NULL, &rect);
}


void render_game_souris(SDL_Window* win, SDL_Renderer* ren, Env * env){
  SDL_Rect rect;
  dir direction_add;
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  SDL_RenderCopy(ren, env->background, NULL, NULL);

  SDL_SetRenderDrawColor(ren, 255,255,255,255);
  SDL_Rect haut;
  haut.x = 10;
  haut.y = 30;
  haut.w = w-20;
  haut.h = 1;
  SDL_RenderFillRect(ren, &haut);

  SDL_Rect bas;
  bas.x = 10;
  bas.y = h-30;
  bas.w = w-20;
  bas.h = 1;
  SDL_RenderFillRect(ren, &bas);

  SDL_Rect gauche;
  gauche.x = 10;
  gauche.y = 30;
  gauche.w = 1;
  gauche.h = h-60;
  SDL_RenderFillRect(ren, &gauche);

  SDL_Rect droite;
  droite.x = w-10;
  droite.y = 30;
  droite.w = 1;
  droite.h = h-60;
  SDL_RenderFillRect(ren, &droite);

  /* render background texture */

  SDL_QueryTexture(env->help, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/4 - rect.w/2; rect.y = h-15 - rect.h/2;
  SDL_RenderCopy(ren, env->help, NULL, &rect);

  SDL_QueryTexture(env->sol, NULL, NULL, &rect.w, &rect.h);
  rect.x = 3*w/4 - rect.w/2; rect.y = h-15 - rect.h/2;
  SDL_RenderCopy(ren, env->sol, NULL, &rect);

  SDL_QueryTexture(env->home, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = 15 - rect.h/2;
  SDL_RenderCopy(ren, env->home, NULL, &rect);
  int x_max = env->x_max;
  int y_max = env->y_max;

  for(int x=0;x<=env->x_max;x++){  // Mise en place des noeuds et de leur degrés dans le render
    for(int y=0;y<=env->y_max;y++){
      int number_node = game_get_node_number(env->n_game,x,y_max-y);
      if(number_node!=-1){
        node n_value = game_node(env->n_game,number_node);
        if(get_required_degree(n_value)==get_degree(env->n_game,number_node)){ // Si le noeud est saturé on change de couleur
        env->nodes[number_node]=env->degreeor[get_required_degree(n_value)];
        }
        else{
        env->nodes[number_node]=env->degree[get_required_degree(n_value)];
        }

        SDL_QueryTexture(env->nodes[number_node], NULL, NULL, &rect.w, &rect.h);
        rect.x = ((w-60)*x/(x_max))+15; rect.y = ((h-90)*y/(y_max))+35;
        env->coordonnes[number_node][0]= rect.x;
        env->coordonnes[number_node][1]= rect.y;
        env->coordonnes[number_node][2]= 25+rect.x;
        env->coordonnes[number_node][3]= 25+rect.y;
        SDL_RenderCopy(ren,env->nodes[number_node], NULL, &rect);

      }
    }
  }

  for(int i = 0;i<env->node_num;i++){    // Mise en place des ponts pour chaque noeud
    node n_value = game_node(env->n_game,i);
    for(direction_add = NORTH;direction_add<=EAST;direction_add++){
      if(get_degree_dir(env->n_game,i,direction_add)>=1){
        int voisin = get_neighbour_dir(env->n_game,i,direction_add);
        if(direction_add==WEST || direction_add==EAST){
          SDL_Rect placement;
          int start_x;
          int between;
          int x0 = env->coordonnes[i][0];
          int x1 = env->coordonnes[voisin][0];
          if(env->coordonnes[i][0]<env->coordonnes[voisin][0]){
             start_x = x0;
             between = x1-x0;
          }
          else{
            start_x = x1;
            between = x0-x1;

          }
          placement.x=start_x+20;
          placement.y=env->coordonnes[i][1];
          placement.w=between-20;
          placement.h=20;
          if(get_degree_dir(env->n_game,i,direction_add)==2){
            SDL_RenderCopy(ren,env->pontdoubleh,NULL,&placement);
          }
          else{
            SDL_RenderCopy(ren,env->pontsimpleh,NULL,&placement);
          }

        }
        else{
          SDL_Rect placement;
          int start_y;
          int between;
          int y0 = env->coordonnes[i][1];
          int y1 = env->coordonnes[voisin][1];
          if(env->coordonnes[i][0]<env->coordonnes[voisin][0]){
             start_y = y0;
             between = y1-y0;
          }
          else{
            start_y = y1;
            between = y0-y1;

          }
          placement.x=env->coordonnes[i][0];
          placement.y=start_y+20;
          placement.w=20;
          placement.h=between-20;
          if(get_degree_dir(env->n_game,i,direction_add)==2){
            SDL_RenderCopy(ren,env->pontdoublev,NULL,&placement);
          }
          else{
            SDL_RenderCopy(ren,env->pontsimplev,NULL,&placement);
          }

        }
      }
    }

  }
}

void render_gagner_souris(SDL_Window* win, SDL_Renderer* ren, Env * env){
  SDL_Rect rect;
  dir direction_add;
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  SDL_RenderCopy(ren, env->background, NULL, NULL);

  SDL_QueryTexture(env->home, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = 15 - rect.h/2;
  SDL_RenderCopy(ren, env->home, NULL, &rect);

  SDL_QueryTexture(env->gagner, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = h/2 - rect.h/2;
  SDL_RenderCopy(ren, env->gagner, NULL, &rect);
}


void render(SDL_Window* win, SDL_Renderer* ren, Env * env){

  if(env->ecran == 0){
    render_menu_souris(win, ren, env);
  }
  else if(env->ecran == 1){
    render_niveau_souris(win, ren, env);
  }
  else if(env->ecran == 2){
    render_regle_souris(win, ren, env);
  }
  else if(env->ecran == 3){
    render_game_souris(win, ren, env);
  }
  else if(env->ecran == 4){
    render_gagner_souris(win, ren, env);
  }
}






/* **************************************************************** */


bool process_menu_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e){
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  if(e->type == SDL_MOUSEMOTION){
    SDL_Point curseur;
    SDL_GetMouseState(&curseur.x, &curseur.y);



    if(curseur.y < 17*h/32 && curseur.y > 15*h/32){
      if(curseur.x < 8*w/12 && curseur.x > 4*w/12){
        env->nouv = env->nouvor;
      }
      else{
        env->nouv = env->nouvbis;
      }
    }
    else if(curseur.y < 21*h/32 && curseur.y > 19*h/32){
      if(curseur.x < 7*w/12 && curseur.x > 5*w/12){
        env->regle = env->regleor;
      }
      else{
        env->regle = env->reglebis;
      }
    }
    else if(curseur.y < 25*h/32 && curseur.y > 23*h/32){
      if(curseur.x < 7*w/12 && curseur.x > 5*w/12){
        env->quitter = env->quitteror;
      }
      else{
        env->quitter = env->quitterbis;
      }
    }
    else{
      env->nouv = env->nouvbis;
      env->regle = env->reglebis;
      env->quitter = env->quitterbis;
    }
  }
  else if(e->type == SDL_MOUSEBUTTONDOWN){
    SDL_Point curseur;
    SDL_GetMouseState(&curseur.x,&curseur.y);
    if(curseur.y < 17*h/32 && curseur.y > 15*h/32){
      if(curseur.x < 8*w/12 && curseur.x > 4*w/12){       /* NOUVELLE PARTIE */
	env->ecran = 1;
	env->nouv = env->nouvbis;
      }
    }
    else if(curseur.y < 21*h/32 && curseur.y > 19*h/32){
      if(curseur.x < 7*w/12 && curseur.x > 5*w/12){    /* REGLES */
	env->ecran = 2;
	env->regle = env->reglebis;
      }
    }
    else if(curseur.y < 25*h/32 && curseur.y > 23*h/32){
      if(curseur.x < 7*w/12 && curseur.x > 5*w/12){ /* QUITTER */
	return true;
      }
    }
  }
  return false;
}


bool process_niveau_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e){
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  if(e->type == SDL_MOUSEMOTION){
    SDL_Point curseur;
    SDL_GetMouseState(&curseur.x, &curseur.y);
    if(curseur.x < 7*w/12 && curseur.x > 5*w/12){
      if(curseur.y < 15*h/32 && curseur.y > 13*h/32){  /* NOUVELLE PARTIE */
	env->easy = env->easyor;
      }
      else if(curseur.y < 19*h/32 && curseur.y > 17*h/32){  /* CHARGER PARTIE */
	env->medium = env->mediumor;
      }
      else if(curseur.y < 23*h/32 && curseur.y > 21*h/32){ /* REGLES */
	env->hard = env->hardor;
      }
      else if(curseur.y < 27*h/32 && curseur.y > 25*h/32){
	env->fleche = env->flecheor;
      }
      else{
	env->easy = env->easybis;
	env->medium = env->mediumbis;
	env->hard = env->hardbis;
	env->fleche = env->flechebis;
      }
    }
    else{
      env->easy = env->easybis;
      env->medium = env->mediumbis;
      env->hard = env->hardbis;
      env->fleche = env->flechebis;
    }
  }
  if(e->type == SDL_MOUSEBUTTONDOWN){
    SDL_Point curseur;
    SDL_GetMouseState(&curseur.x,&curseur.y);
    if(curseur.x < 7*w/12 && curseur.x > 5*w/12){
      if(curseur.y < 15*h/32 && curseur.y > 13*h/32){
	env->ecran = 3;
	env->easy = env->easybis;
	init_game_SDL(env,"../src/game_default.txt");
      }
      if(curseur.y < 19*h/32 && curseur.y > 17*h/32){
	env->ecran = 3;
	env->medium = env->mediumbis;
	init_game_SDL(env,"../src/game_easy.txt");
      }
      if(curseur.y < 23*h/32 && curseur.y > 21*h/32){
	env->ecran = 3;
	env->hard = env->hardbis;
	init_game_SDL(env,"../src/game_medium.txt");
      }
      else if(curseur.y < 27*h/32 && curseur.y > 25*h/32){ /* QUITTER */
	env->ecran = 0;
	env->fleche = env->flechebis;
      }
    }
  }
  return false;
}


bool process_regle_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e){
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  if(e->type == SDL_MOUSEMOTION){
    SDL_Point curseur;
    SDL_GetMouseState(&curseur.x, &curseur.y);
    if(curseur.x < 2*w/33){
      if(curseur.y > 60*h/66){
	env->fleche = env->flecheor;
      }
      else{
	env->fleche = env->flechebis;
      }
    }
    else{
      env->fleche = env->flechebis;
    }
  }
  else if(e->type == SDL_MOUSEBUTTONDOWN){
    SDL_Point curseur;
    SDL_GetMouseState(&curseur.x, &curseur.y);
    if(curseur.x < 2*w/33){
      if(curseur.y > 60*h/66){
	env->ecran = 0;
	env->fleche = env->flechebis;
      }
    }
  }
  return false;
}


bool process_game_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e){

  if(game_over(env->n_game) && env->solved == true){
    SDL_Delay(2000);
    env->ecran = 4;
  }  //
  if(game_over(env->n_game) && env->solved == false){
    env->ecran = 4;
  }

  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  if(e->type == SDL_MOUSEMOTION){                                                 //
    SDL_Point curseur;                                                            //
    SDL_GetMouseState(&curseur.x, &curseur.y);
    for(int i = 0;i<env->node_num;i++){
      int x_w = env->coordonnes[i][2];
      int y_h = env->coordonnes[i][3];
      if(curseur.x>env->coordonnes[i][0] && curseur.x<x_w){
        if(curseur.y>env->coordonnes[i][1] && curseur.y<y_h){
          node n_value = game_node(env->n_game,i);
        }
      }

    }
    //
    if(curseur.x > 3*w/16 && curseur.x < 5*w/16){ //Aide
      if(curseur.y > h - 30){
      env->help = env->helpor;
      }
      else{                                                                       //
       env->help = env->helpbis;                                                 //
      }
    }
    else{                                                                       //
       env->help = env->helpbis;                                                 //
      }

    if(curseur.x > 5*w/8 && curseur.x < 7*w/8){ //Solution
      if(curseur.y > h-30){
      env->sol = env->solor;
      }
      else{                                                                       //
       env->sol = env->solbis;                                                 //
      }
    }
    else{                                                                       //
       env->sol = env->solbis;                                                 //
      }

    if(curseur.x > 3*w/8 && curseur.x < 5*w/8){                                   // Acceuil
      if(curseur.y < 30){                                 //
	       env->home = env->homeor;                                                  //
      }                                                                           //
      else{                                                                       //
	     env->home = env->homebis;                                                 //
      }                                                                           // Process du jeu
    }                                                                             // Événements du jeu
    else{                                                                         //
      env->home = env->homebis;                                                   //
    }                                                                             //
  }                                                                               //
  if(e->type == SDL_MOUSEBUTTONDOWN){                                             //
    SDL_Point curseur;                                                            //
    SDL_GetMouseState(&curseur.x, &curseur.y);                                    //
    if(curseur.x > 3*w/8 && curseur.x < 5*w/8){                                   //
      if(curseur.y < 30){                                 //
	env->ecran = 0;                                                           //
	env->home = env->homebis;
	clean_game_SDL(env);
      }                                                                           //
    }
    if(curseur.x > 3*w/16 && curseur.x < 5*w/16){ //Aide
      if(curseur.y > h - 30){
        if(env->help_count==0){
          int c = env->node_num;
          int random = rand()%c;
          env->help_count = 1;
          play_auto(env->n_game,random);
          env->help = env->helpbis;
        }
      }
    }


    if(curseur.x > 5*w/8 && curseur.x < 7*w/8){
    	if(curseur.y > h - 30){
        env->solved = true;
        env->sol = env->solbis;
    		solveur(env->n_game);
    	}
    }

    for(int i = 0;i<env->node_num;i++){
      int x_w = env->coordonnes[i][2];
      int y_h = env->coordonnes[i][3];
      if(curseur.x>env->coordonnes[i][0] && curseur.x<x_w){
        if(curseur.y>env->coordonnes[i][1] && curseur.y<y_h){
          node n_value = game_node(env->n_game,i);
          int lock = env->lock;
          if(lock==0){
            env->nodes_to_add[0]=i;
            env->lock++;
          }
          if(lock==4){
            env->nodes_to_add[1]=i;
            env->lock++;

          }
          if(env->lock==8){
            add_bridge_SDL(env,ren);
            env->lock=0;
          }
        }
      }

    }                                                                             //
  }                                                                               //
  return false;                                                                   //
}

bool process_gagner_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e){
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  if(e->type == SDL_MOUSEMOTION){
    SDL_Point curseur;
    SDL_GetMouseState(&curseur.x, &curseur.y);
    if(curseur.x > 3*w/8 && curseur.x < 5*w/8){
      if(curseur.y < 30){
	env->home = env->homeor;
      }
      else{
	env->home = env->homebis;
      }
    }
    else{
      env->home = env->homebis;
    }
  }
  if(e->type == SDL_MOUSEBUTTONDOWN){
    SDL_Point curseur;
    SDL_GetMouseState(&curseur.x, &curseur.y);
    if(curseur.x > 3*w/8 && curseur.x < 5*w/8){
      if(curseur.y < 30){
	env->ecran = 0;
	env->home = env->homebis;
	clean_game_SDL(env);
      }
    }
  }
}


bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{
  /* generic events */
  if (e->type == SDL_QUIT) {
    return true;
  }

  else if(env->ecran == 0){
    return process_menu_souris(win, ren, env, e);
  }

  else if(env->ecran == 1){
    return process_niveau_souris(win, ren, env, e);
  }

  else if(env->ecran == 2){
    return process_regle_souris(win, ren, env, e);
  }
  else if(env->ecran == 3){
    return process_game_souris(win, ren, env, e);
  }
  else if(env->ecran == 4){
    return process_gagner_souris(win, ren, env, e);
  }
  return false;
}


void add_bridge_SDL(Env * env, SDL_Renderer * ren){
  dir direction_add;
  node n_value = game_node(env->n_game,env->nodes_to_add[0]);
  for(direction_add = NORTH;direction_add<=EAST;direction_add++){
    if(get_neighbour_dir(env->n_game,env->nodes_to_add[0],direction_add)==env->nodes_to_add[1]){
      if(can_add_bridge_dir(env->n_game,env->nodes_to_add[0],direction_add)){
        add_bridge_dir(env->n_game,env->nodes_to_add[0],direction_add);
      }
      else if(get_degree_dir(env->n_game,env->nodes_to_add[0],direction_add)>=1 && !can_add_bridge_dir(env->n_game,env->nodes_to_add[0],direction_add)){
        del_bridge_SDL(env,ren,direction_add);
      }
    }
  }

}


void del_bridge_SDL(Env * env,SDL_Renderer * ren,dir direction_add){
  del_bridge_dir(env->n_game,env->nodes_to_add[0],direction_add);
  del_bridge_dir(env->n_game,env->nodes_to_add[0],direction_add);
}

void init_game_SDL(Env * env,char * argv){
  int nb_dir; // Nombre de direction
  int node_val; //Nombre de noeuds
  int nb_max_br; //Nombre de ponts max
  int size_max; //Taille maximal de la grille
  node *tab_n = node_init_mem(&node_val,&nb_dir,&nb_max_br,&size_max,argv);
  env->tab_n = tab_n;
  env->n_game = new_game(node_val,tab_n,nb_max_br,nb_dir);
  env->node_num = node_val;
  env->ecran = 3;
  env->load=1;

  for(int i=0;i<node_val;i++){
    node node_degree = game_node(env->n_game, i);
    int x = get_x(node_degree);
    int y = get_y(node_degree);
    if(x > env->x_max){
      env->x_max = x;
    }
    if(y > env->y_max){
      env->y_max = y;
    }
  }

}

void clean_game_SDL(Env* env){
  if(env->x_max!=0 && env->y_max!=0){
    free_tab(env->tab_n,env->node_num);
    delete_game(env->n_game);
    env->x_max=0,env->y_max=0;
    env->help_count = 0;
  }
}





/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */
  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->titre);
  SDL_DestroyTexture(env->nouv);
  SDL_DestroyTexture(env->nouvbis);
  SDL_DestroyTexture(env->nouvor);
  SDL_DestroyTexture(env->regle);
  SDL_DestroyTexture(env->reglebis);
  SDL_DestroyTexture(env->regleor);
  SDL_DestroyTexture(env->regletitre);
  SDL_DestroyTexture(env->regle1);
  SDL_DestroyTexture(env->regle2);
  SDL_DestroyTexture(env->regle3);
  SDL_DestroyTexture(env->regle3bis);
  SDL_DestroyTexture(env->regle4);
  SDL_DestroyTexture(env->regle4bis);
  SDL_DestroyTexture(env->quitter);
  SDL_DestroyTexture(env->quitterbis);
  SDL_DestroyTexture(env->quitteror);
  SDL_DestroyTexture(env->choix);
  SDL_DestroyTexture(env->choixbis);
  SDL_DestroyTexture(env->easy);
  SDL_DestroyTexture(env->easybis);
  SDL_DestroyTexture(env->easyor);
  SDL_DestroyTexture(env->medium);
  SDL_DestroyTexture(env->mediumbis);
  SDL_DestroyTexture(env->mediumor);
  SDL_DestroyTexture(env->hard);
  SDL_DestroyTexture(env->hardbis);
  SDL_DestroyTexture(env->hardor);
  SDL_DestroyTexture(env->help);
  SDL_DestroyTexture(env->helpbis);
  SDL_DestroyTexture(env->helpor);
  SDL_DestroyTexture(env->sol);
  SDL_DestroyTexture(env->solbis);
  SDL_DestroyTexture(env->solor);
  SDL_DestroyTexture(env->home);
  SDL_DestroyTexture(env->homebis);
  SDL_DestroyTexture(env->homeor);
  SDL_DestroyTexture(env->fleche);
  SDL_DestroyTexture(env->flechebis);
  SDL_DestroyTexture(env->flecheor);
  SDL_DestroyTexture(env->gagner);
  SDL_DestroyTexture(env->tmp);
  SDL_DestroyTexture(env->degree);
  SDL_DestroyTexture(env->degreeor);
  SDL_DestroyTexture(env->nodes);
  SDL_DestroyTexture(env->un);
  SDL_DestroyTexture(env->deux);
  SDL_DestroyTexture(env->trois);
  SDL_DestroyTexture(env->quatre);
  SDL_DestroyTexture(env->cinq);
  SDL_DestroyTexture(env->six);
  SDL_DestroyTexture(env->sept);
  SDL_DestroyTexture(env->huit);
  SDL_DestroyTexture(env->pontsimpleh);
  SDL_DestroyTexture(env->pontdoubleh);
  SDL_DestroyTexture(env->pontsimplev);
  SDL_DestroyTexture(env->pontdoubleh);
  SDL_DestroyTexture(env->coordonnes[500][4]);



  free(env);
}

/* **************************************************************** */
