#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmod.h>
#include "../Headers/enums.h"
#include "../Headers/structs.h"
#include "../Headers/utils.h"
#include <windows.h>
//#inlude <SDL/sdlgfx.h>

/* Tanks */

int tank_apparition(Player* player, int* limitApparationTank)
{
	int result = 0;

	if(*limitApparationTank == 0 && player->posY > 380)
	{
		*limitApparationTank = 1;
		result = 1;
	}
	if(*limitApparationTank == 1 && player->posY < 380)
	{
		*limitApparationTank = 0;
		result = 0;
	}
	if(*limitApparationTank == 0 && player->posY > 380)
	{
		*limitApparationTank = 1;
		result = 0;
	}
	return result;
}

void tank_generation(Player* player, Tank* tanks, int* nbTanks)
{
	int i = (*nbTanks);
	int random = 0;
	tanks[i].position.y = 410;

	if(player->posX > 150)
	{
		switch(player->moveDirection)
		{
			case MOVE_TOLEFT:
				tanks[i].position.x = player->posX - 640;
				break;
			case MOVE_TOLEFTIDLE:
				tanks[i].position.x = player->posX - 640;
				break;
			case MOVE_TOFACE:
				random = random_range(0, 99);
				random = random % 2;
				if(!random)
					tanks[i].position.x = player->posX + 640;
				else
					tanks[i].position.x = player->posX - 640;
				break;
			case MOVE_TORIGHT:
				tanks[i].position.x = player->posX + 640;
				break;
			case MOVE_TORIGHTIDLE:
				tanks[i].position.x = player->posX + 640;
				break;
			default:
				break;
		}
		tanks[i].lifes = 1;
		tanks[i].death = 0;
		(*nbTanks) ++;
	}
}

void tank_moving(Tank* tanks, Player* player, int* nbTanks, int* tempsPrecedent6, int* tempsActuel6)
{
	int i;
	int positionPlayer;

	*tempsActuel6 = SDL_GetTicks();
	if(*tempsActuel6 - *tempsPrecedent6 > 100)
	{
		tanks->animation ++;
		tanks->animation = tanks->animation % 3;
		*tempsPrecedent6 = *tempsActuel6;
	}

	for(i = 0; i < (*nbTanks); i++)
	{
		positionPlayer = player->posX;
		if(positionPlayer + 12 < tanks[i].position.x + (tanks[i].crop.w / 2) + 1)
		{
			tanks[i].moveStageX = MOVE_LEFT;
		}
		if(positionPlayer + 12 > tanks[i].position.x + (tanks[i].crop.w / 2) + 1)
		{
			tanks[i].moveStageX = MOVE_RIGHT;

		}
		if(positionPlayer + 12 == tanks[i].position.x + (tanks[i].crop.w / 2) + 1)
		{
			tanks[i].moveStageX = MOVE_IDLE;
		}
		/*for(k = 0; k < (*nbTanks); k++)
		{
			if(!((tanks[i].position.x >= tanks[k].position.x + tanks[k].crop.w) || (tanks[i].position.x + tanks[i].crop.w <= tanks[k].position.x) || (tanks[i].position.y >= tanks[k].position.y + tanks[k].crop.h) || (tanks[i].position.y + tanks[i].crop.h <= tanks[k].position.y)))
			{
				tanks[i].moveStageX = MOVE_IDLE;
			}
		}*/
		if(tanks->lifes != 0)
		{
			switch(tanks[i].moveStageX)
			{
				case(MOVE_RIGHT):
					if(tanks->animation == 0)
					{
						tanks[i].crop.x = 161;
						tanks[i].crop.y = 9;
						tanks[i].crop.w = 63;
						tanks[i].crop.h = 48;
					}
					if(tanks->animation == 1)
					{
						tanks[i].crop.x = 87;
						tanks[i].crop.y = 9;
						tanks[i].crop.w = 63;
						tanks[i].crop.h = 48;
					}
					if(tanks->animation == 2)
					{
						tanks[i].crop.x = 12;
						tanks[i].crop.y = 9;
						tanks[i].crop.w = 63;
						tanks[i].crop.h = 48;
					}
					tanks[i].position.x += 2;
					break;
				case(MOVE_LEFT):
					if(tanks->animation == 0)
					{
						tanks[i].crop.x = 161;
						tanks[i].crop.y = 9;
						tanks[i].crop.w = 63;
						tanks[i].crop.h = 48;
					}
					if(tanks->animation == 1)
					{
						tanks[i].crop.x = 87;
						tanks[i].crop.y = 9;
						tanks[i].crop.w = 63;
						tanks[i].crop.h = 48;
					}
					if(tanks->animation == 2)
					{
						tanks[i].crop.x = 12;
						tanks[i].crop.y = 9;
						tanks[i].crop.w = 63;
						tanks[i].crop.h = 48;
					}
					tanks[i].position.x -= 2;
					break;
				case(MOVE_IDLE):
					tanks[i].crop.x = 161;
					tanks[i].crop.y = 9;
					tanks[i].crop.w = 63;
					tanks[i].crop.h = 48;
				break;
				default:
					break;
			}
		}
	}
}

/* Saucers */

int saucer_apparition(Player* player, int* limitApparationSaucer, int* nbMissiles) //Plus on spam les missiles, plus les soucoupes se génèrent
{
	int result = 0;

	if(*nbMissiles > 3 && *limitApparationSaucer == 0)
	{
		*limitApparationSaucer = 1;
		result = 1;
	}
	if(*limitApparationSaucer == 1 && *nbMissiles > 3)
	{
		result = 0;
	}
	if(*nbMissiles < 4)
	{
		*limitApparationSaucer = 0;
		result = 0;
	}
	return result;
}

void saucer_generation(Player* player, Saucer* saucers, int* nbSaucers)
{
	int i = (*nbSaucers);
	int random = 0;
	saucers[i].position.y = player->posY;

	if(player->posY < 400 && player->posX > 150)
	{
		switch(player->moveDirection)
		{
			case MOVE_TOLEFT:
				saucers[i].position.x = player->posX + 640;
				break;
			case MOVE_TOLEFTIDLE:
				saucers[i].position.x = player->posX + 640;
				break;
			case MOVE_TOFACE:
				random = random_range(0, 99);
				random = random % 2;
				if(!random)
					saucers[i].position.x = player->posX + 640;
				else
					saucers[i].position.x = player->posX - 640;
				break;
			case MOVE_TORIGHT:
				saucers[i].position.x = player->posX - 640;
				break;
			case MOVE_TORIGHTIDLE:
				saucers[i].position.x = player->posX - 640;
				break;
			default:
				break;
		}
		saucers[i].lifes = 1;
		saucers[i].death = 0;
		(*nbSaucers) ++;
	}
}

void saucer_moving(Saucer* saucers, Player* player, int* nbSaucers, int* tempsPrecedent9, int* tempsActuel9)
{
	int i;

	*tempsActuel9= SDL_GetTicks();
	if(*tempsActuel9 - *tempsPrecedent9 > 25)
	{
		saucers->animation ++;
		saucers->animation = saucers->animation % 12;
		*tempsPrecedent9 = *tempsActuel9;
	}

	for(i = 0; i < (*nbSaucers); i++)
	{
		if(player->lifes != 0)
			saucers[i].position.y = player->posY;

		if(saucers[i].lifes != 0)
		{
						if(player->posX < saucers[i].position.x)
				saucers[i].position.x -= 8;
			if(player->posX > saucers[i].position.x)
				saucers[i].position.x += 8;

			if(saucers->animation == 0)
			{
				saucers[i].crop.x = 4;
				saucers[i].crop.y = 28;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 1)
			{
				saucers[i].crop.x = 60;
				saucers[i].crop.y = 28;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 2)
			{
				saucers[i].crop.x = 116;
				saucers[i].crop.y = 28;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 3)
			{
				saucers[i].crop.x = 172;
				saucers[i].crop.y = 28;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 4)
			{
				saucers[i].crop.x = 228;
				saucers[i].crop.y = 28;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 5)
			{
				saucers[i].crop.x = 4;
				saucers[i].crop.y = 71;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 6)
			{
				saucers[i].crop.x = 60;
				saucers[i].crop.y = 71;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 7)
			{
				saucers[i].crop.x = 116;
				saucers[i].crop.y = 71;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 8)
			{
				saucers[i].crop.x = 172;
				saucers[i].crop.y = 71;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 9)
			{
				saucers[i].crop.x = 228;
				saucers[i].crop.y = 71;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 10)
			{
				saucers[i].crop.x = 4;
				saucers[i].crop.y = 112;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
			if(saucers->animation == 11)
			{
				saucers[i].crop.x = 60;
				saucers[i].crop.y = 112;
				saucers[i].crop.w = 53;
				saucers[i].crop.h = 31;
			}
		}
	}
}

/* Planes */

int plane_apparition(Player* player, int* limitApparationPlane)
{
	int result = 0;

	if(*limitApparationPlane == 0 && player->posY < 120)
	{
		*limitApparationPlane = 1;
		result = 1;
	}
	if(*limitApparationPlane == 1 && player->posY > 120)
	{
		*limitApparationPlane = 0;
		result = 0;
	}
	if(*limitApparationPlane == 0 && player->posY < 120)
	{
		*limitApparationPlane = 1;
		result = 0;
	}
	return result;
}

void plane_generation(Player* player, Plane* planes, int* nbPlanes)
{
	int i = (*nbPlanes);
	int random = 0;
	planes[i].position.y = player->posY;

	if(player->posY < 400 && player->posX > 150)
	{
		switch(player->moveDirection)
		{
			case MOVE_TOLEFT:
				planes[i].position.x = player->posX + 640;
				planes[i].moveStageX = MOVE_LEFT;
				break;
			case MOVE_TOLEFTIDLE:
				planes[i].position.x = player->posX + 640;
				planes[i].moveStageX = MOVE_LEFT;
				break;
			case MOVE_TOFACE:
				random = random_range(0, 99);
				random = random % 2;
				if(!random)
				{
					planes[i].position.x = player->posX + 640;
					planes[i].moveStageX = MOVE_LEFT;
				}
				else
				{
					planes[i].position.x = player->posX - 640;
					planes[i].moveStageX = MOVE_RIGHT;
				}
				break;
			case MOVE_TORIGHT:
				planes[i].position.x = player->posX - 640;
				planes[i].moveStageX = MOVE_RIGHT;
				break;
			case MOVE_TORIGHTIDLE:
				planes[i].position.x = player->posX - 640;
				planes[i].moveStageX = MOVE_RIGHT;
				break;
			default:
				break;
		}
		planes[i].lifes = 1;
		planes[i].death = 0;
		(*nbPlanes) ++;
	}
}

void plane_moving(Plane* planes, Player* player, int* nbPlanes, int* tempsPrecedent11, int* tempsActuel11)
{
	int i, j;

	*tempsActuel11= SDL_GetTicks();
	if(*tempsActuel11 - *tempsPrecedent11 > 100)
	{
		planes->animation ++;
		planes->animation = planes->animation % 22;
		*tempsPrecedent11 = *tempsActuel11;
	}

	for(i = 0; i < (*nbPlanes); i++)
	{
		if(planes[i].lifes != 0)
		{
			if(planes[i].moveStageX == MOVE_RIGHT)
			{
				if(planes->animation == 0 || planes->animation == 1 || planes->animation == 2 || planes->animation == 15 || planes->animation == 16 || planes->animation == 17 || planes->animation == 18 || planes->animation == 19 || planes->animation == 20 || planes->animation == 21)
				{
					planes[i].crop.x = 7;
					planes[i].crop.y = 58;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes->animation == 3)
				{
					planes[i].crop.x = 74;
					planes[i].crop.y = 56;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes->animation == 4)
				{
					planes[i].crop.x = 140;
					planes[i].crop.y = 56;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes->animation == 5)
				{
					planes[i].crop.x = 208;
					planes[i].crop.y = 56;
					planes[i].crop.w = 55;
					planes[i].crop.h = 26;
				}
				if(planes->animation == 6)
				{
					planes[i].crop.x = 275;
					planes[i].crop.y = 56;
					planes[i].crop.w = 55;
					planes[i].crop.h = 26;
				}
				if(planes->animation == 11)
				{
					planes[i].crop.x = 275;
					planes[i].crop.y = 56;
					planes[i].crop.w = 55;
					planes[i].crop.h = 26;
				}
				if(planes->animation == 12)
				{
					planes[i].crop.x = 208;
					planes[i].crop.y = 56;
					planes[i].crop.w = 55;
					planes[i].crop.h = 26;
				}
				if(planes->animation == 13)
				{
					planes[i].crop.x = 140;
					planes[i].crop.y = 56;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes->animation == 14)
				{
					planes[i].crop.x = 74;
					planes[i].crop.y = 56;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				planes[i].position.x += 10;
			}
			if(planes[i].moveStageX == MOVE_LEFT)
			{
				if(planes->animation == 0 || planes->animation == 1 || planes->animation == 2 || planes->animation == 15 || planes->animation == 16 || planes->animation == 17 || planes->animation == 18 || planes->animation == 19 || planes->animation == 20 || planes->animation == 21)
				{
					planes[i].crop.x = 279;
					planes[i].crop.y = 12;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes->animation == 3)
				{
					planes[i].crop.x = 212;
					planes[i].crop.y = 10;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes->animation == 4)
				{
					planes[i].crop.x = 146;
					planes[i].crop.y = 10;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes->animation == 5)
				{
					planes[i].crop.x = 78;
					planes[i].crop.y = 10;
					planes[i].crop.w = 55;
					planes[i].crop.h = 26;
				}
				if(planes->animation == 6)
				{
					planes[i].crop.x = 11;
					planes[i].crop.y = 10;
					planes[i].crop.w = 55;
					planes[i].crop.h = 26;
				}
				if(planes->animation == 11)
				{
					planes[i].crop.x = 11;
					planes[i].crop.y = 10;
					planes[i].crop.w = 55;
					planes[i].crop.h = 26;
				}
				if(planes->animation == 12)
				{
					planes[i].crop.x = 78;
					planes[i].crop.y = 10;
					planes[i].crop.w = 55;
					planes[i].crop.h = 26;
				}
				if(planes->animation == 13)
				{
					planes[i].crop.x = 146;
					planes[i].crop.y = 10;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				if(planes->animation == 14)
				{
					planes[i].crop.x = 212;
					planes[i].crop.y = 10;
					planes[i].crop.w = 55;
					planes[i].crop.h = 27;
				}
				planes[i].position.x -= 10;
			}
		}
		if(planes[i].position.x > 5081 || planes[i].position.x < 0)
		{
			for(j = i; j < (*nbPlanes)-1; j++)
			{
				planes[j] = planes[j+1];
			}
			*nbPlanes -= 1;
		}
	}
}

/* Gestion des missiles des avions */

void missilesPlanes(PlaneMissiles* planesMissiles, Player* player, int* nbPlanesMissiles, int* nbPlanes,  Plane* planes, int* tempsPrecedent13, int* tempsActuel13)
{
	int i, j;
	int n = (*nbPlanesMissiles);

	*tempsActuel13= SDL_GetTicks();

	if(*tempsActuel13 - *tempsPrecedent13 > 1000)
	{
		for(i = 0; i < (*nbPlanes); i++)
		{
			if(planes[i].lifes != 0)
			{
				if(planes[i].moveStageX == MOVE_RIGHT)
				{
					planesMissiles[n].position.x = planes[i].position.x + (planes[i].crop.w / 2);
					planesMissiles[n].position.y = planes[i].position.y + (planes[i].crop.h / 2);
					planesMissiles[n].crop.x = 10;
					planesMissiles[n].crop.y = 5;
					planesMissiles[n].crop.w = 4;
					planesMissiles[n].crop.h = 2;
					planesMissiles[n].moveStageX = MOVE_RIGHT;
					(*nbPlanesMissiles) ++;
				}
				if(planes[i].moveStageX == MOVE_LEFT)
				{
					planesMissiles[n].position.x = planes[i].position.x + (planes[i].crop.w / 2);
					planesMissiles[n].position.y = planes[i].position.y + (planes[i].crop.h / 2);
					planesMissiles[n].crop.x = 4;
					planesMissiles[n].crop.y = 5;
					planesMissiles[n].crop.w = 4;
					planesMissiles[n].crop.h = 2;
					planesMissiles[n].moveStageX = MOVE_LEFT;
					(*nbPlanesMissiles) ++;
				}
			}
		}
		*tempsPrecedent13 = *tempsActuel13;
	}


	for(i = 0; i < (*nbPlanesMissiles); i++)
	{
		if(planesMissiles[i].position.x > 5081 || planesMissiles[i].position.x < 0)
		{
			for(j = i; j < (*nbPlanesMissiles)-1; j++)
			{
				planesMissiles[j] = planesMissiles[j+1];
			}
			*nbPlanesMissiles -= 1;
		}
		else
		{
			switch(planesMissiles[i].moveStageX)
			{
				case(MOVE_RIGHT):
					planesMissiles[i].position.x += 12;
					break;
				case(MOVE_LEFT):
					planesMissiles[i].position.x -= 12;
					break;
				default:
					break;
			}
		}
	}
}

/* Apparition aléatoire des ennemies */

int enemy_randomness(Level* level, int* tempsPrecedent8, int* tempsActuel8)
{
	int resultat = 4;
	int i;

	*tempsActuel8 = SDL_GetTicks();
	if(*tempsActuel8 - *tempsPrecedent8 > 1000)
	{
		for(i=0; i<3; i++)
		{
			switch(i)
			{
				case 0:
					resultat = random_range(0, level->tanksRandomness);
					break;
				case 1:
					resultat = random_range(0, level->planesRandomness);
					break;
				case 2:
					resultat = random_range(0, level->saucersRandomness);
					break;
			}
			if(resultat < 4)
			{
				break;
			}
		}
		*tempsPrecedent8 = *tempsActuel8;
	}
	return resultat;
}

/* Hotages */

void hostages_generation(int* buildingPosX, Hostages* hostages, int* nbHostages)
{
	int i = (*nbHostages);
	hostages[i].position.y = 400;
	hostages[i].position.x = *buildingPosX;
	(*nbHostages) ++;
}

void hostages_moving(Hostages* hostages, Player* player, int* nbHostages, int* tempsPrecedent14, int* tempsActuel14)
{
	int i, j;
	int positionPlayer;

	for(i = 0; i < (*nbHostages); i++)
	{
		positionPlayer = player->posX;
		if(positionPlayer < hostages[i].position.x)
		{
			hostages[i].moveStageX = MOVE_LEFT;
		}
		if(positionPlayer > hostages[i].position.x)
		{
			hostages[i].moveStageX = MOVE_RIGHT;
		}
		if(positionPlayer == hostages[i].position.x)
		{
			hostages[i].moveStageX = MOVE_IDLE;
		}
	}

	*tempsActuel14 = SDL_GetTicks();
	if(*tempsActuel14 - *tempsPrecedent14 > 50)
	{
		hostages->animation ++;
		hostages->animation = hostages->animation % 5;
		*tempsPrecedent14 = *tempsActuel14;
	}

	for(i = 0; i < (*nbHostages); i++)
	{
		if(!((hostages[i].position.x >= player->posX + player->sprite->rect->w) || (hostages[i].position.x + hostages[i].crop.w <= player->posX) || (hostages[i].position.y >= player->posY + player->sprite->rect->h) || (hostages[i].position.y + hostages[i].crop.h <= player->posY)) && player->hostages < 16)
		{
			for(j = i; j < (*nbHostages)-1; j++)
			{
				hostages[j] = hostages[j+1];
			}
			*nbHostages -= 1;
			player->hostages += 16;
		}
		else
		{
			switch(hostages[i].moveStageX)
			{
				case(MOVE_RIGHT):
					hostages[i].position.x += 1;
					if(hostages->animation == 0)
					{
						hostages[i].crop.x = 0;
						hostages[i].crop.y = 18;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					if(hostages->animation == 1)
					{
						hostages[i].crop.x = 0;
						hostages[i].crop.y = 37;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					if(hostages->animation == 2)
					{
						hostages[i].crop.x = 0;
						hostages[i].crop.y = 56;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					if(hostages->animation == 3)
					{
						hostages[i].crop.x = 0;
						hostages[i].crop.y = 75;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					if(hostages->animation == 4)
					{
						hostages[i].crop.x = 0;
						hostages[i].crop.y = 94;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					break;
				case(MOVE_LEFT):
					hostages[i].position.x -= 1;
					if(hostages->animation == 0)
					{
						hostages[i].crop.x = 68;
						hostages[i].crop.y = 18;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					if(hostages->animation == 1)
					{
						hostages[i].crop.x = 68;
						hostages[i].crop.y = 37;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					if(hostages->animation == 2)
					{
						hostages[i].crop.x = 68;
						hostages[i].crop.y = 56;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					if(hostages->animation == 3)
					{
						hostages[i].crop.x = 68;
						hostages[i].crop.y = 75;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					if(hostages->animation == 4)
					{
						hostages[i].crop.x = 68;
						hostages[i].crop.y = 94;
						hostages[i].crop.w = 62;
						hostages[i].crop.h = 16;
					}
					break;
				case(MOVE_IDLE):
					hostages[i].crop.x = 0;
					hostages[i].crop.y = 0;
					hostages[i].crop.w = 62;
					hostages[i].crop.h = 16;
					break;
				default:
					break;
			}
		}
	}
}


