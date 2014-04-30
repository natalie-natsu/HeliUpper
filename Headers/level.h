#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <SDL/SDL.h>
#include "../Headers/structs.h"

void updateLevel(Level* level, SDL_Surface* ecran);
void scrollLevel(Level* level, int axis, float speed);
void levelParameters(Level* level);


#endif // LEVEL_H_INCLUDED
