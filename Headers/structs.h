#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
#include <SDL/SDL.h>
#include "enums.h"

typedef struct Sprite
{
	SDL_Surface* surface;
	SDL_Rect* rect;
} Sprite;

typedef struct Player
{
	Sprite* sprite;
	movements moveStageX;
	movements moveStageY;
	movedir moveDirection;
	float posX, posY;
	int lifes, hostages, spritestage, score, animation, death, safeHostages;

} Player;

typedef struct Level
{
    Sprite* sprite;
    int level, hostages, score, chrono, num, tanksRandomness, planesRandomness, saucersRandomness;
    float groundLevel;
    Player* playerInstance;
    Sprite* dynamic;
    Sprite* screen;
} Level;

typedef struct Missiles
{
	SDL_Rect position, crop;
	int animation;
	movements moveStageX, moveStageY;
} Missiles;


typedef struct Tank
{
	SDL_Rect position, crop;
	int animation, lifes, death;
	movements moveStageX, moveStageY;
} Tank;


typedef struct Plane
{
	SDL_Rect position, crop;
	int animation, lifes, death;
	movements moveStageX, moveStageY;
} Plane;


typedef struct PlaneMissiles
{
	SDL_Rect position, crop;
	movements moveStageX, moveStageY;
} PlaneMissiles;


typedef struct Saucer
{
	SDL_Rect position, crop;
	int animation, lifes, death;
	movements moveStageX, moveStageY;
} Saucer;


typedef struct Building
{
	SDL_Rect position, crop;
	int lifes;
} Building;

typedef struct Hostages
{
	SDL_Rect position, crop;
	int animation, lifes;
	movements moveStageX, moveStageY;
	movedir moveDirection;
} Hostages;

#endif // STRUCTS_H_INCLUDED
