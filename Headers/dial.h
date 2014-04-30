#ifndef DIAL_H_INCLUDED
#define DIAL_H_INCLUDED
#include <SDL/SDL.h>
#include <windows.h>
#include <fmod.h>
#include <SDL/SDL_image.h>
#include "..\Headers\structs.h"

int dialog (SDL_Surface *screen, FMOD_SYSTEM* system, int* lvl);

#endif // DIAL_H_INCLUDED
