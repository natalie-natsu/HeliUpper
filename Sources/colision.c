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

void collision(Hostages* hostages, int* nbHostages, Building* buildings, Missiles* missiles, PlaneMissiles* planesMissiles, Tank* tanks, Plane* planes, Saucer* saucers, Player* player, int* nbTanks, int* nbPlanes, int* nbSaucers, int* nbMissiles, int* nbPlanesMissiles, int* tempsPrecedent7, int* tempsActuel7, int* tempsPrecedent10, int* tempsActuel10, int* tempsPrecedent12, int* tempsActuel12, FMOD_SYSTEM* system)
{
	int i, j, k;
	/*FMOD_SOUND *explosion;
    FMOD_System_CreateSound(system, "Sounds/explosionHelico.mp3", FMOD_CREATESAMPLE, 0, &explosion);
    FMOD_SOUND *dammages;
    FMOD_System_CreateSound(system, "Sounds/dammages.mp3", FMOD_CREATESAMPLE, 0, &dammages);*/

	/* Collisions Player - Ennemis */

	//Tanks
	for(i = 0; i < *nbTanks; i++)
	{
		if(!((tanks[i].position.x >= player->posX + player->sprite->rect->w) || (tanks[i].position.x + tanks[i].crop.w <= player->posX) || (tanks[i].position.y >= player->posY + player->sprite->rect->h) || (tanks[i].position.y + tanks[i].crop.h <= player->posY)))
		{
			if(player->lifes != 0)
			{
				tanks[i].lifes = 0;
				//FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, dammages, 0, NULL);
				if(tanks[i].death == 1)
					player->lifes --;
			}
			/*else
			{
				FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, explosion, 0, NULL);
			}*/
		}
	}
	//Planes
	for(i = 0; i < *nbPlanes; i++)
	{
		if(!((planes[i].position.x >= player->posX + player->sprite->rect->w) || (planes[i].position.x + planes[i].crop.w <= player->posX) || (planes[i].position.y >= player->posY + player->sprite->rect->h) || (planes[i].position.y + planes[i].crop.h <= player->posY)))
		{
			if(player->lifes != 0)
			{
				planes[i].lifes = 0;
				//FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, dammages, 0, NULL);
				if(planes[i].death == 1)
					player->lifes --;
			}
			/*else
			{
				FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, explosion, 0, NULL);
			}*/
		}
	}
	//Saucers
	for(i = 0; i < *nbSaucers; i++)
	{
		if(!((saucers[i].position.x >= player->posX + player->sprite->rect->w) || (saucers[i].position.x + saucers[i].crop.w <= player->posX) || (saucers[i].position.y >= player->posY + player->sprite->rect->h) || (saucers[i].position.y + saucers[i].crop.h <= player->posY)))
		{
			if(player->lifes != 0)
			{
				saucers[i].lifes = 0;
				//FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, dammages, 0, NULL);
				if(saucers[i].death == 1)
					player->lifes --;
			}
			/*else
			{
				FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, explosion, 0, NULL);
			}*/
		}
	}

	/* Collisions Missiles - Ennemis */

	//Tanks
	for(i = 0; i < *nbTanks; i++)
	{
		for(k = 0; k < *nbMissiles; k++)
		{
			if(!((tanks[i].position.x >= missiles[k].position.x + missiles[k].crop.w) || (tanks[i].position.x + tanks[i].crop.w <= missiles[k].position.x) || (tanks[i].position.y >= missiles[k].position.y + missiles[k].crop.h) || (tanks[i].position.y + tanks[i].crop.h <= missiles[k].position.y)))
			{
				if(player->lifes != 0)
				{
					tanks[i].lifes = 0;
					for(j = k; j < (*nbMissiles)-1; j++)
					{
						missiles[j] = missiles[j+1];
					}
					*nbMissiles -= 1;
					player->score += 5;
				}
			}
		}
	}
	//Planes
	for(i = 0; i < *nbPlanes; i++)
	{
		for(k = 0; k < *nbMissiles; k++)
		{
			if(!((planes[i].position.x >= missiles[k].position.x + missiles[k].crop.w) || (planes[i].position.x + planes[i].crop.w <= missiles[k].position.x) || (planes[i].position.y >= missiles[k].position.y + missiles[k].crop.h) || (planes[i].position.y + planes[i].crop.h <= missiles[k].position.y)))
			{
				if(player->lifes != 0)
				{
					planes[i].lifes = 0;
					for(j = k; j < (*nbMissiles)-1; j++)
					{
						missiles[j] = missiles[j+1];
					}
					*nbMissiles -= 1;
					player->score += 15;
				}
			}
		}
	}
	//Saucers
	for(i = 0; i < *nbSaucers; i++)
	{
		for(k = 0; k < *nbMissiles; k++)
		{
			if(!((saucers[i].position.x >= missiles[k].position.x + missiles[k].crop.w) || (saucers[i].position.x + saucers[i].crop.w <= missiles[k].position.x) || (saucers[i].position.y >= missiles[k].position.y + missiles[k].crop.h) || (saucers[i].position.y + saucers[i].crop.h <= missiles[k].position.y)))
			{
				if(player->lifes != 0)
				{
					saucers[i].lifes = 0;
					for(j = k; j < (*nbMissiles)-1; j++)
					{
						missiles[j] = missiles[j+1];
					}
					*nbMissiles -= 1;
					player->score += 10;
				}
			}
		}
	}

	/* Collisions Missiles - Player */

	//Planes
	for(k = 0; k < *nbPlanesMissiles; k++)
	{
		if(!((planesMissiles[k].position.x >= player->posX + player->sprite->rect->w) || (planesMissiles[k].position.x + planesMissiles[k].crop.w <= player->posX) || (planesMissiles[k].position.y >= player->posY + player->sprite->rect->h) || (planesMissiles[k].position.y + planesMissiles[k].crop.h <= player->posY)))
		{
			if(player->lifes != 0)
			{
				for(j = k; j < (*nbPlanesMissiles)-1; j++)
				{
					planesMissiles[j] = planesMissiles[j+1];
				}
				*nbPlanesMissiles -= 1;
				//FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, dammages, 0, NULL);
				player->lifes --;
				/*if(player->lifes == 0)
				{
					FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, explosion, 0, NULL);
				}*/
			}
		}
	}

	/* Collisions Hotages - Ennemis */

	//Tanks
	for(i = 0; i < *nbTanks; i++)
	{
		for(k = 0; k < *nbHostages; k++)
		{
			if(!((tanks[i].position.x >= hostages[k].position.x + hostages[k].crop.w) || (tanks[i].position.x + tanks[i].crop.w <= hostages[k].position.x) || (tanks[i].position.y >= hostages[k].position.y + hostages[k].crop.h) || (tanks[i].position.y + tanks[i].crop.h <= hostages[k].position.y)))
			{
				for(j = k; j < (*nbHostages)-1; j++)
				{
					hostages[j] = hostages[j+1];
				}
				*nbHostages -= 1;
			}
		}
	}

	/* Collisions Missiles - Hostages */

	for(i = 0; i < *nbHostages; i++)
	{
		for(k = 0; k < *nbMissiles; k++)
		{
			if(!((hostages[i].position.x >= missiles[k].position.x + missiles[k].crop.w) || (hostages[i].position.x + hostages[i].crop.w <= missiles[k].position.x) || (hostages[i].position.y >= missiles[k].position.y + missiles[k].crop.h) || (hostages[i].position.y + hostages[i].crop.h <= missiles[k].position.y)))
			{
				for(j = k; j < (*nbMissiles)-1; j++)
				{
					missiles[j] = missiles[j+1];
				}
				*nbMissiles -= 1;
				for(j = k; j < (*nbHostages)-1; j++)
				{
					hostages[j] = hostages[j+1];
				}
				*nbHostages -= 1;
			}
		}
	}

	/* Animation de mort et de dommages */

	//Saucers
	for(i = 0; i < *nbSaucers; i++)
	{
		if(saucers[i].lifes == 0)
		{
			if(saucers[i].death == 0)
			{
				saucers[i].crop.x = 116;
				saucers[i].crop.y = 112;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers[i].death== 1)
			{
				for(j = i; j < (*nbSaucers)-1; j++)
				{
					saucers[j] = saucers[j+1];
				}
				*nbSaucers -= 1;
			}
			*tempsActuel10= SDL_GetTicks();
			if(*tempsActuel10 - *tempsPrecedent10 > 100)
			{
				saucers[i].death ++;
				saucers[i].death = saucers[i].death % 2;
				*tempsPrecedent10 = *tempsActuel10;
			}
		}
	}

	//Planes
	for(i = 0; i < *nbPlanes; i++)
	{
		if(planes[i].lifes == 0)
		{
			if(planes[i].death == 0)
			{
				if(planes[i].moveStageX == MOVE_LEFT)
				{
					planes[i].crop.x = 279;
					planes[i].crop.y = 102;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes[i].moveStageX == MOVE_RIGHT)
				{
					planes[i].crop.x = 6;
					planes[i].crop.y = 102;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
			}
			if(planes[i].death== 1)
			{
				for(j = i; j < (*nbPlanes)-1; j++)
				{
					planes[j] = planes[j+1];
				}
				*nbPlanes -= 1;
			}
			*tempsActuel12= SDL_GetTicks();
			if(*tempsActuel12 - *tempsPrecedent12 > 100)
			{
				planes[i].death ++;
				planes[i].death = planes[i].death % 2;
				*tempsPrecedent12 = *tempsActuel12;
			}
		}
	}

	//Tanks
	for(i = 0; i < *nbTanks; i++)
	{
		if(tanks[i].lifes == 0)
		{
			if(tanks[i].death == 0)
			{
				tanks[i].crop.x = 241;
				tanks[i].crop.y = 9;
				tanks[i].crop.w = 63;
				tanks[i].crop.h = 48;
			}
			if(tanks[i].death== 1)
			{
				for(j = i; j < (*nbTanks)-1; j++)
				{
					tanks[j] = tanks[j+1];
				}
				*nbTanks -= 1;
			}
			*tempsActuel7= SDL_GetTicks();
			if(*tempsActuel7 - *tempsPrecedent7 > 100)
			{
				tanks[i].death ++;
				tanks[i].death = tanks[i].death % 2;
				*tempsPrecedent7 = *tempsActuel7;
			}
		}
	}
	/*FMOD_SoundGroup_Release(dammages);
	FMOD_SoundGroup_Release(explosion);*/
}


int collisionBuilding(int* nbMissiles, Building* buildings, Missiles* missiles)
{
	/* Collisions Missiles - Buildings */

	int i, j, k;
	int resultat = 5;

	for(i = 0; i < 5; i++)
	{
		if(buildings[i].lifes != 0)
		{
			for(k = 0; k < *nbMissiles; k++)
			{
				if(!((buildings[i].position.x >= missiles[k].position.x + missiles[k].crop.w) || (buildings[i].position.x + buildings[i].crop.w <= missiles[k].position.x) || (buildings[i].position.y >= missiles[k].position.y + missiles[k].crop.h) || (buildings[i].position.y + buildings[i].crop.h <= missiles[k].position.y)))
				{
					for(j = k; j < (*nbMissiles)-1; j++)
					{
						missiles[j] = missiles[j+1];
					}
					*nbMissiles -= 1;
					buildings[i].lifes --;
					if(buildings[i].lifes == 0)
					{
						resultat = i;
					}
					break;
					break;
				}
			}
		}
	}
	return resultat;
}
