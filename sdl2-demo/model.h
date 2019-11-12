// SDL2 Model by aurelien.esnard@u-bordeaux.fr

#ifndef MODEL_H
#define MODEL_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "node.h"
#include "init_game.h"


typedef struct Env_t Env;

/* **************************************************************** */
     
#ifdef __ANDROID__ 
#define PRINT(STR, ...) do { SDL_Log(STR, ##__VA_ARGS__);  } while(0)
#define ERROR(STR, ...) do { SDL_Log(STR, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0) 
// #define LOG(TAG, STR, ...) __android_log_print(ANDROID_LOG_VERBOSE, TAG ,STR, ##__VA_ARGS__)
# else
#define PRINT(STR, ...) do { printf(STR, ##__VA_ARGS__); } while(0)
#define ERROR(STR, ...) do { fprintf(stderr, STR, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#endif

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]);

//Render

void render_menu_souris(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render_niveau_souris(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render_regle_souris(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render_game_souris(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render_gagner_souris(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render(SDL_Window* win, SDL_Renderer* ren, Env * env);

//Process

bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_menu_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_niveau_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_regle_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_game_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_gagner_souris(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);

//Fonctions auxiliaires

void add_bridge_SDL(Env * env, SDL_Renderer * ren);
void del_bridge_SDL(Env * env,SDL_Renderer * ren,dir direction_add);
void init_game_SDL(Env * env,char * argv);
void clean_game_SDL(Env* env);
void clean(SDL_Window* win, SDL_Renderer* ren, Env * env);



/* **************************************************************** */

#endif
