#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "structs.h"
#include "enums.h"

void updatePlayerSprite(Player* player, int* tempsPrecedent1, int* tempsActuel1, int* tempsPrecedent3, int* tempsActuel3, int* dammage);
void movePlayer(Player* player, Level* level);
void initPlayer(Player* player);
void missilesPlayer(Missiles* missiles, Player* player, SDL_Surface* screen, int* nbMissiles, int* tempsPrecedent4, int* tempsActuel4);
void handleMissiles(SDLKey key, Player* player, Missiles* missiles, int* nbMissiles, int* tempsPrecedent5, int* tempsActuel5);

#endif // PLAYER_H_INCLUDED
