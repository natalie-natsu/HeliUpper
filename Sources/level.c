#include "..\Headers\structs.h"
#include "..\Headers\level.h"
#include "..\Headers\player.h"
#include <time.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void updateLevel(Level* level, SDL_Surface* ecran)
{

    float posX = (level->playerInstance->posX)-(level->sprite->rect->x);
    float rel = posX/640;
    if(rel >= 0.83)
    {

        outputLog("RIGHT");
        //int levelSpeed = (((player.posX / ecran->w)-0.75)*30);
        int levelSpeed = 6;
        if(level->playerInstance->moveDirection == MOVE_TORIGHT)
            scrollLevel(level, 1, levelSpeed);
    }
    else if(rel <= 0.16)
    {
        //int levelSpeed = (abs(((player.posX / ecran->w)-0.25))*30);
        outputLog("LEFT");
        int levelSpeed = 6;
        if(level->playerInstance->moveDirection == MOVE_TOLEFT)
            scrollLevel(level, 0, levelSpeed);
    }
    movePlayer(level->playerInstance, level);
}

void scrollLevel(Level* level, int axis, float speed)
{
    float newX;
    if(axis == 1) // AXIS == 1 == DROITE
    {

        newX = level->sprite->rect->x + speed;
        if(newX >= level->sprite->rect->w-640)
        {
            newX = level->sprite->rect->w-640;
        }

        level->sprite->rect->x = newX;

    }
    else
    {
        newX = level->sprite->rect->x - speed;
        if(newX <= 0)
        {
            newX = 0;
        }
        level->sprite->rect->x = newX;
    }

}

void levelParameters(Level* level)
{
	switch(level->num)
	{
		case 1:
			level->hostages = 32;
			level->chrono = 180;
			level->score = 200;
			level->tanksRandomness = 50; // 1 chance sur 50 de voir appaitre un tank chaque seconde.
			level->planesRandomness = 50; // 1 chance sur 100 de voir appaitre un avion chaque seconde.
			level->saucersRandomness = 50; // 1 chance sur 50 de voir appaitre une soucoupe volante chaque seconde.
			level->sprite->surface = IMG_Load("graphism/background/background1.png");
			break;
		case 2:
			level->hostages = 32;
			level->chrono = 180;
			level->score = 400;
			level->tanksRandomness = 30;
			level->planesRandomness = 30;
			level->saucersRandomness = 30;
			level->sprite->surface = IMG_Load("graphism/background/background1.png");
			break;
		case 3:
			level->hostages = 40;
			level->chrono = 180;
			level->score = 400;
			level->tanksRandomness = 40;
			level->planesRandomness = 40;
			level->saucersRandomness = 40;
			level->sprite->surface = IMG_Load("graphism/background/background1.png");
			break;
		case 4:
			level->hostages = 48;
			level->chrono = 220;
			level->score = 500;
			level->tanksRandomness = 30;
			level->planesRandomness = 30;
			level->saucersRandomness = 30;
			level->sprite->surface = IMG_Load("graphism/background/background2.png");
			break;
		case 5:
			level->hostages = 16;
			level->chrono = 60;
			level->score = 300;
			level->tanksRandomness = 20;
			level->planesRandomness = 20;
			level->saucersRandomness = 20;
			level->sprite->surface = IMG_Load("graphism/background/background2.png");
			break;
		case 6:
			level->hostages = 50;
			level->chrono = 240;
			level->score = 500;
			level->tanksRandomness = 30;
			level->planesRandomness = 30;
			level->saucersRandomness = 30;
			level->sprite->surface = IMG_Load("graphism/background/background2.png");
			break;
		case 7:
			level->hostages = 56;
			level->chrono = 300;
			level->score = 700;
			level->tanksRandomness = 25;
			level->planesRandomness = 25;
			level->saucersRandomness = 25;
			level->sprite->surface = IMG_Load("graphism/background/background3.png");
			break;
		case 8:
			level->hostages = 64;
			level->chrono = 190;
			level->score = 400;
			level->tanksRandomness = 40;
			level->planesRandomness = 40;
			level->saucersRandomness = 40;
			level->sprite->surface = IMG_Load("graphism/background/background3.png");
			break;
		case 9:
			level->hostages = 72;
			level->chrono = 140;
			level->score = 440;
			level->tanksRandomness = 80;
			level->planesRandomness = 80;
			level->saucersRandomness = 80;
			level->sprite->surface = IMG_Load("graphism/background/background4.png");
			break;
		case 10:
			level->hostages = 72;
			level->chrono = 240;
			level->score = 750;
			level->tanksRandomness = 30;
			level->planesRandomness = 30;
			level->saucersRandomness = 30;
			level->sprite->surface = IMG_Load("graphism/background/background4.png");
			break;
		case 11:
			level->hostages = 80;
			level->chrono = 200;
			level->score = 800;
			level->tanksRandomness = 15;
			level->planesRandomness = 15;
			level->saucersRandomness = 15;
			level->sprite->surface = IMG_Load("graphism/background/background5.png");
			break;
		case 12:
			level->hostages = 80;
			level->chrono = 666;
			level->score = 30000;
			level->tanksRandomness = 5;
			level->planesRandomness = 5;
			level->saucersRandomness = 5;
			level->sprite->surface = IMG_Load("graphism/background/background6.png");
			break;
		default:
			break;
	}
}
