#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmod.h>
#include <time.h>
#include "../Headers/enums.h"
#include "../Headers/structs.h"
#include "../Headers/utils.h"
#include "../Headers/ia.h"
#include <windows.h>
//#inlude <SDL/sdlgfx.h>


void updatePlayerSprite(Player* player, int* tempsPrecedent1, int* tempsActuel1, int* tempsPrecedent3, int* tempsActuel3, int* dammage)
{
	*tempsActuel1 = SDL_GetTicks();
	if(player->lifes != 0)
	{
		if(*tempsActuel1 - *tempsPrecedent1 > 120)
		{
			player->animation ++;
			player->animation = player->animation % 2;
			*tempsPrecedent1 = *tempsActuel1;
		}
	}

	if(player->lifes != 0)
	{
		/*if(*dammage != player->lifes)
		{
			player->sprite->surface = IMG_Load("Sprites/Heli/helidamages.gif");
			SDL_SetColorKey(player->sprite->surface, SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite->surface->format, 9, 113, 255));
			switch(player->moveDirection)
			{
				case MOVE_TORIGHT:
					if(player->animation == 0)
					{
						player->sprite->rect->x = 178;
						player->sprite->rect->y = 2;
						player->sprite->rect->w = 38;
						player->sprite->rect->h = 31;
					}
					else
					{
						player->sprite->rect->x = 133;
						player->sprite->rect->y = 2;
						player->sprite->rect->w = 38;
						player->sprite->rect->h = 31;
					}
					break;
				case MOVE_TORIGHTIDLE:
					if(player->animation == 0)
					{
						player->sprite->rect->x = 98;
						player->sprite->rect->y = 0;
						player->sprite->rect->w = 28;
						player->sprite->rect->h = 36;
					}
					else
					{
						player->sprite->rect->x = 66;
						player->sprite->rect->y = 0;
						player->sprite->rect->w = 28;
						player->sprite->rect->h = 36;
					}
					break;
				case MOVE_TOFACE:
					if(player->animation == 0)
					{
						player->sprite->rect->x = 32;
						player->sprite->rect->y = 0;
						player->sprite->rect->w = 28;
						player->sprite->rect->h = 36;
					}
					else
					{
						player->sprite->rect->x = 0;
						player->sprite->rect->y = 0;
						player->sprite->rect->w = 28;
						player->sprite->rect->h = 36;
					}
					break;
				case MOVE_TOLEFT:
					if(player->animation == 0)
					{
						player->sprite->rect->x = 0;
						player->sprite->rect->y = 38;
						player->sprite->rect->w = 38;
						player->sprite->rect->h = 31;
					}
					else
					{
						player->sprite->rect->x = 45;
						player->sprite->rect->y = 38;
						player->sprite->rect->w = 38;
						player->sprite->rect->h = 31;
					}
					break;
				case MOVE_TOLEFTIDLE:
					if(player->animation == 0)
					{
						player->sprite->rect->x = 90;
						player->sprite->rect->y = 36;
						player->sprite->rect->w = 28;
						player->sprite->rect->h = 36;
					}
					else
					{
						player->sprite->rect->x = 121;
						player->sprite->rect->y = 36;
						player->sprite->rect->w = 28;
						player->sprite->rect->h = 36;
					}
					break;
				default:
					break;
			}
			*dammage = player->lifes;
		}
		else
		{*/
			switch(player->moveDirection)
			{
				case MOVE_TOLEFT:
					player->sprite->surface = IMG_Load("Sprites/Heli/helimouvementredleft.gif");
					SDL_SetColorKey(player->sprite->surface, SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite->surface->format, 9, 113, 255));
					if(player->animation == 0)
					{
						player->sprite->rect->x = 0;
						player->sprite->rect->w = 38;
					}
					else
					{
						player->sprite->rect->x = 46;
						player->sprite->rect->w = 37;
					}
					if(player->posY > 410)
					{
						player->lifes = 0;
					}
					break;
				case MOVE_TOLEFTIDLE:
					player->sprite->surface = IMG_Load("Sprites/Heli/helimouvementredleft.gif");
					SDL_SetColorKey(player->sprite->surface, SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite->surface->format, 9, 113, 255));
					if(player->animation == 0)
					{
						player->sprite->rect->x = 91;
						player->sprite->rect->w = 28;
					}
					else
					{
						player->sprite->rect->x = 122;
						player->sprite->rect->w = 28;
					}
					break;
				case MOVE_TOFACE:
					player->sprite->surface = IMG_Load("Sprites/Heli/helimouvementred.gif");
					SDL_SetColorKey(player->sprite->surface, SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite->surface->format, 9, 113, 255));
					if(player->animation == 0)
					{
						player->sprite->rect->x = 0;
						player->sprite->rect->w = 27;
					}
					else
					{
						player->sprite->rect->x = 31;
						player->sprite->rect->w = 27;
					}
					break;
				case MOVE_TORIGHT:
					player->sprite->surface = IMG_Load("Sprites/Heli/helimouvementred.gif");
					SDL_SetColorKey(player->sprite->surface, SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite->surface->format, 9, 113, 255));
					if(player->animation == 0)
					{
						player->sprite->rect->x = 134;
						player->sprite->rect->w = 37;
					}
					else
					{
						player->sprite->rect->x = 179;
						player->sprite->rect->w = 38;
					}
					if(player->posY > 410)
					{
						player->lifes = 0;
					}
					break;
				case MOVE_TORIGHTIDLE:
					player->sprite->surface = IMG_Load("Sprites/Heli/helimouvementred.gif");
					SDL_SetColorKey(player->sprite->surface, SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite->surface->format, 9, 113, 255));
					if(player->animation == 0)
					{
						player->sprite->rect->x = 67;
						player->sprite->rect->w = 28;
					}
					else
					{
						player->sprite->rect->x = 98;
						player->sprite->rect->w = 28;
					}
					break;
				default:
					break;
			}
		//}
	}

    if(player->lifes == 0)
	{
		*tempsActuel3 = SDL_GetTicks();
		if(*tempsActuel3 - *tempsPrecedent3 > 500)
		{
			player->death ++;
			*tempsPrecedent1 = *tempsActuel1;
		}

		player->sprite->surface = IMG_Load("Sprites/Heli/heliexplosion.gif");
		SDL_SetColorKey(player->sprite->surface, SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite->surface->format, 9, 113, 255));

		if(player->death == 0)
		{
			player->sprite->rect->x = 35;
			player->sprite->rect->w = 30;
		}
		if(player->death == 1)
		{
			player->sprite->rect->x = 70;
			player->sprite->rect->w = 32;
		}
		if(player->death == 2)
		{
			player->sprite->rect->x = 109;
			player->sprite->rect->w = 32;
		}
		if(player->death == 3)
		{
			player->sprite->rect->x = 149;
			player->sprite->rect->w = 32;
		}
		if(player->death == 4)
		{
			player->sprite->rect->x = 188;
			player->sprite->rect->w = 32;
		}
		if(player->death == 5)
		{
			player->sprite->rect->x = 226;
			player->sprite->rect->w = 32;
		}
		if(player->death == 6)
		{
			player->sprite->rect->x = 0;
			player->sprite->rect->w = 31;
		}
	}
}


void movePlayer(Player* player, Level* level) // Mouvements du joueur
{
	if(player->posX < 0)
	{
		player->posX = 0;
	}
	if(player->posY < 0)
	{
		player->posY = 0;
	}
	if(player->posX > 2695)
	{
		player->posX = 2695;
	}
	if(player->posY > 410)
	{
		player->posY = 410;
	}

	switch(player->moveStageY)
    {
        case MOVE_UP:
        	if(player->lifes != 0)
			{
				player->posY -= 2;
			}
            break;
        case MOVE_DOWN:
        	if(player->lifes != 0)
			{
				player->posY += 2;
			}
            break;
        case MOVE_IDLE:
        	if(player->lifes != 0)
			{
				player->posY += 0.05;
			}
            else
			{
				player->posY += 2;
			}
            break;
        default:
            break;
    }
    switch(player->moveStageX)
    {
        case(MOVE_RIGHT):
			if(player->lifes != 0)
			{
				player->posX = player->posX+6;
			}
            break;
        case(MOVE_LEFT):
			if(player->lifes != 0)
			{
				player->posX = player->posX-6;
			}
            break;
        default:
            break;
	}
    if(player->posY > (480-player->sprite->rect->h))
    {
        player->posY = 480-player->sprite->rect->h;
    }
}

void missilesPlayer(Missiles* missiles, Player* player, SDL_Surface* screen, int* nbMissiles, int* tempsPrecedent4, int* tempsActuel4)
{
	int i, j;

	*tempsActuel4 = SDL_GetTicks();
	if(*tempsActuel4 - *tempsPrecedent4 > 50)
	{
		missiles->animation ++;
		missiles->animation = missiles->animation % 2;
		*tempsPrecedent4 = *tempsActuel4;
	}

	for(i = 0; i < (*nbMissiles); i++)
	{
		if(missiles[i].position.x > 5081 || missiles[i].position.y > 480 || missiles[i].position.x < 0 || missiles[i].position.y < 0)
		{
			for(j = i; j < (*nbMissiles)-1; j++)
			{
				missiles[j] = missiles[j+1];
			}
			*nbMissiles -= 1;
		}
		else
		{
			switch(missiles[i].moveStageX)
			{
				case(MOVE_RIGHT):
					missiles[i].position.x += 8;
					break;
				case(MOVE_LEFT):
					missiles[i].position.x -= 8;
					break;
				default:
					break;
			}
			switch(missiles[i].moveStageY)
			{
				case(MOVE_DOWN):
					missiles[i].position.y += 8;
					break;
				default:
					break;
			}
			if(missiles->animation == 0)
			{
				missiles[i].crop.x = 0;
			}
			else
			{
				missiles[i].crop.x = 11;
			}
		}
	}
}

void handleMissiles(SDLKey key, Player* player, Missiles* missiles, int* nbMissiles, int* tempsPrecedent5, int* tempsActuel5) // Prise en charge des touches pour les missiles
{
	int i = (*nbMissiles);
	missiles[i].position.x = player->posX + (player->sprite->rect->w / 2);
	missiles[i].position.y = player->posY + (player->sprite->rect->h / 2);
	missiles[i].crop.x = 0;
	missiles[i].crop.y = 0;
	missiles[i].crop.w = 8;
	missiles[i].crop.h = 8;

	*tempsActuel5 = SDL_GetTicks();
	if(*tempsActuel5 - *tempsPrecedent5 > 250 && player->lifes != 0)
	{
		switch(key)
		{
			case SDLK_l:
				missiles[i].moveStageX = MOVE_LEFT;
				missiles[i].moveStageY = MOVE_DOWN;
				(*nbMissiles) ++;
				break;
			case SDLK_SEMICOLON:
				missiles[i].moveStageX = MOVE_RIGHT;
				missiles[i].moveStageY = MOVE_DOWN;
				(*nbMissiles) ++;
				break;
			case SDLK_o:
				missiles[i].moveStageX = MOVE_LEFT;
				missiles[i].moveStageY = MOVE_IDLE;
				(*nbMissiles) ++;
				break;
			case SDLK_p:
				missiles[i].moveStageX = MOVE_RIGHT;
				missiles[i].moveStageY = MOVE_IDLE;
				(*nbMissiles) ++;
				break;
			case SDLK_SPACE:
				missiles[i].moveStageX = MOVE_IDLE;
				missiles[i].moveStageY = MOVE_DOWN;
				(*nbMissiles) ++;
				break;
			default:
				break;
		}
		*tempsPrecedent5 = *tempsActuel5;
	}
}
