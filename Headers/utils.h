#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <SDL/SDL.h>
#include <windows.h>
#include <fmod.h>
#include <SDL/SDL_image.h>
#include "..\Headers\structs.h"

//Déclaration des prototypes
void handleKey(SDLKey key, int state, Player* player);
int titleScreen(SDL_Surface* screen, FMOD_SYSTEM* system);
int victory(SDL_Surface* screen, FMOD_SYSTEM* system, Level* level);
int gameover(SDL_Surface* screen, FMOD_SYSTEM* system);
int mdp(SDL_Surface* screen, FMOD_SYSTEM* system, FMOD_SOUND* choiceTitle);
int gameLoop(SDL_Surface* ecran, FMOD_SYSTEM* system, int* lvl);
void outputLog(const char* logStr);
int random_range (int min, int max);
void gameInfos (SDL_Surface* screen, Player* player, Level* level, int* tempsPrecedent2, int* tempsActuel2);
int transition(SDL_Surface* screen);
void intro(SDL_Surface* screen, FMOD_SYSTEM* system);
void credits(SDL_Surface* screen);

#endif // UTILS_H_INCLUDED
