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
#include "../Headers/colision.h"
#include <windows.h>
//#inlude <SDL/sdlgfx.h>




///////////////////////////////////////////////////////////////////////
//                                                                   //
//                        The Game Loop                              //
//                                                                   //
///////////////////////////////////////////////////////////////////////




int gameLoop(SDL_Surface* ecran, FMOD_SYSTEM* system, int* lvl)
{
	/* Variables communes */

    int continuer = 1;
    int i, j, explosionSound = 1;
    int newGame = 0;

	/* Définitions de times servant essentiellement à l'animation */

    int tempsPrecedent1 = 0, tempsActuel1 = 0; // Animations de l'hélico
    int tempsPrecedent2 = 0, tempsActuel2 = 0; // Chrono
    int tempsPrecedent3 = 0, tempsActuel3 = 0; // Explosion de l'hélico
	int tempsPrecedent4 = 0, tempsActuel4 = 0; // Missiles de l'hélico
	int tempsPrecedent5 = 0, tempsActuel5 = 0; // Limite de missiles par seconde
	int tempsPrecedent6 = 0, tempsActuel6 = 0; // Animation des tanks
	int tempsPrecedent7 = 0, tempsActuel7 = 0; // Destructions des tanks
	int tempsPrecedent8 = 0, tempsActuel8 = 0; // Apparition aléatoire des ennemies
	int tempsPrecedent9 = 0, tempsActuel9 = 0; // Animation des saucers
	int tempsPrecedent10 = 0, tempsActuel10 = 0; // Destruction des saucers
	int tempsPrecedent11 = 0, tempsActuel11 = 0; // Animation des avions
	int tempsPrecedent12 = 0, tempsActuel12 = 0; // Destruction des avions
	int tempsPrecedent13 = 0, tempsActuel13 = 0; // Gestion des missiles de l'avion
	int tempsPrecedent14 = 0, tempsActuel14 = 0; // Animation des hotages
	int tempsPrecedent15 = 0, tempsActuel15 = 0; // Victory

	/* Variables SDL, Struct... */

    SDL_Event event;
    SDL_Surface *surface = NULL, *building = NULL, *dynamicEvents = NULL, *rescueZone = NULL, *levelBuilding = NULL, *missile = NULL, *tank = NULL, *plane = NULL, *saucer = NULL, *planeMissile = NULL, *hostage = NULL, *victoryText = NULL;
	dynamicEvents = SDL_CreateRGBSurface(SDL_HWSURFACE, 5081, 480, 32, 0, 0, 0, 0);
    SDL_Rect screenRect, spriteRect, bckgRect, glRect, dynamicRect, positionRescueZone, positionLevelBuilding, positionVictoryText;

    TTF_Init();
    TTF_Font *font = NULL;
    font = TTF_OpenFont("graphism/police/unispace.ttf", 30);
    SDL_Color white = {255, 255, 255};
    victoryText = TTF_RenderText_Blended(font, "[VICTORY]", white);
    positionVictoryText.x = ecran->w / 2;
	positionVictoryText.y = ecran->h / 2;

    FMOD_SOUND *gameMainSound;

    Player player;
    Level level;
    Sprite sprite, lvlSprite, scrSprite;
    Sprite dynamic;
    Missiles missiles[1000];
    PlaneMissiles planesMissiles[1000];
    Tank tanks[1000];
	Plane planes[1000];
    Saucer saucers[1000];
    Building buildings[5];
    Hostages hostages[100];


	/* Définition du level */

    level.sprite = &lvlSprite;
    level.dynamic = &dynamic;
    level.playerInstance = &player;
    level.screen = &scrSprite;
    level.num = *lvl;
    levelParameters(&level);

    /* Cas pour les différents levels */

	switch(level.num)
	{
		case 1:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone1.png");
			FMOD_System_CreateSound(system, "Sounds/starbeamer.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 2:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone2.png");
			FMOD_System_CreateSound(system, "Sounds/spacesynth.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 3:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone3.png");
			FMOD_System_CreateSound(system, "Sounds/laser.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 4:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone4.png");
			FMOD_System_CreateSound(system, "Sounds/battlepixs.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 5:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone5.png");
			FMOD_System_CreateSound(system, "Sounds/gameLoop.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 6:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone6.png");
			FMOD_System_CreateSound(system, "Sounds/supercheesy.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 7:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone7.png");
			FMOD_System_CreateSound(system, "Sounds/gurkenbalken.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 8:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone8.png");
			FMOD_System_CreateSound(system, "Sounds/princess.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 9:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone9.png");
			FMOD_System_CreateSound(system, "Sounds/chaoz.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 10:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZone10.png");
			FMOD_System_CreateSound(system, "Sounds/knights.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 11:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZoneFinal.png");
			FMOD_System_CreateSound(system, "Sounds/DragonForce-TtFaF.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		case 12:
			levelBuilding = IMG_Load("graphism/rescueZone/rescueZoneBonus.png");
			FMOD_System_CreateSound(system, "Sounds/Trololo.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameMainSound);
			break;
		default:
			break;
	}
	FMOD_Sound_SetLoopCount(gameMainSound, -1);

    /* Definition du background */

    bckgRect.x = 0;
    bckgRect.y = 0;
    bckgRect.h = 480;
    bckgRect.w = 5081;
    lvlSprite.rect = &bckgRect;
    glRect.x = 0;
    glRect.y = 0;
    glRect.h = 480;
    glRect.w = 640;
    scrSprite.surface = ecran;
    scrSprite.rect = &glRect;

	/* Définition des missiles */

	int nbMissiles = 0;
	missiles->animation = 0;
	missile = IMG_Load("Sprites/Heli/helibullet.gif");
	SDL_SetColorKey(missile, SDL_SRCCOLORKEY, SDL_MapRGB(missile->format, 9, 113, 255));

	int nbPlanesMissiles = 0;
	planeMissile = IMG_Load("Sprites/Plane/plane.gif");
	SDL_SetColorKey(missile, SDL_SRCCOLORKEY, SDL_MapRGB(missile->format, 9, 113, 255));

	/* Définition des ennemies */

	//Tanks
	int nbTanks = 0;
	int limitApparationTank = 0;
	tanks->animation = 0;
	tanks->death = 0;
	tank = IMG_Load("Sprites/Tank/tank.gif");
	SDL_SetColorKey(tank, SDL_SRCCOLORKEY, SDL_MapRGB(tank->format, 9, 113, 255));
	//Planes
	int nbPlanes = 0;
	int limitApparationPlane = 0;
	planes->animation = 0;
	planes->death = 0;
	plane = IMG_Load("Sprites/Plane/plane.gif");
	SDL_SetColorKey(plane, SDL_SRCCOLORKEY, SDL_MapRGB(plane->format, 9, 113, 255));
	//Saucer
	int nbSaucers = 0;
	int limitApparationSaucer = 0;
	saucers->animation = 0;
	saucers->death = 0;
	saucer = IMG_Load("Sprites/Saucer/saucer.png");
	SDL_SetColorKey(saucer, SDL_SRCCOLORKEY, SDL_MapRGB(saucer->format, 9, 113, 255));

	/* Définition des hotages */

	int nbHostages = 0;
	int newHostage = 10;
	hostages->animation = 0;
	hostages->lifes = 1;
	hostage = IMG_Load("Sprites/Hostages/hostages.png");
	SDL_SetColorKey(hostage, SDL_SRCCOLORKEY, SDL_MapRGB(hostage->format, 9, 113, 255));

	/* Level */

	dynamicRect.x = 0;
	dynamicRect.y = 0;
	dynamicRect.h = 480;
	dynamicRect.w = 5081;
	dynamic.surface = dynamicEvents;
	dynamic.rect = &dynamicRect;
	level.dynamic = &dynamic;
	level.screen = ecran;

	/*Définitions des buildings */

	srand ((int) time (NULL));
	rescueZone = IMG_Load("graphism/rescueZone/rescueBuilding.png");
    positionRescueZone.x = 5;
	positionRescueZone.y = 300;
	positionLevelBuilding.x = 120;
	positionLevelBuilding.y = 300;

	building = IMG_Load("graphism/hostageZone/hostageZone.png");
    for(i=0;i<5;i++)
	{
		buildings[i].position.y = 320;
		buildings[i].crop.w = 90;
		buildings[i].crop.h = 89;
		buildings[i].crop.x = 0;
		buildings[i].crop.y = 0;
		buildings[i].lifes = 5;
		int validBuilding;
		do
		{
			buildings[i].position.x = random_range(640, 2600);
			for(j=0; j<i; j++)
			{
				if(buildings[j].position.x - 105 < buildings[i].position.x && buildings[i].position.x < buildings[j].position.x+105)
				{
					validBuilding = 1;
					break;
				}
				else
					validBuilding = 0;
			}
		}
		while(validBuilding == 1);
	}

    /* Initialisation des données initiales du joueur. */

    player.posX = 50;
    player.posY = 420;

    player.sprite = &sprite;
    player.sprite->surface = surface;
    player.sprite->rect = &spriteRect;
    player.sprite->surface = IMG_Load("Sprites/Heli/helimouvementred.gif");
	SDL_SetColorKey(player.sprite->surface, SDL_SRCCOLORKEY, SDL_MapRGB(player.sprite->surface->format, 9, 113, 255));

	player.sprite->rect->h = 36;
	player.sprite->rect->w = 27;
	player.sprite->rect->x = 0;
	player.sprite->rect->y = 0;

	player.lifes = 3;
	player.score = 0;
	player.hostages = 0;
	player.animation = 0;
	player.death = 0;
	player.safeHostages = 0;
	int dammage = player.lifes;

	/* Début de la boucle du jeu */

	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, gameMainSound, 0, NULL);
    while (continuer)
    {
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
						FMOD_Sound_Release(gameMainSound);
						continuer = 0;
						break;
				case SDL_KEYDOWN:
						handleKey(event.key.keysym.sym, 1, &player);
						handleMissiles(event.key.keysym.sym, &player, missiles, &nbMissiles, &tempsPrecedent5, &tempsActuel5);
						break;
				case SDL_KEYUP:
						handleKey(event.key.keysym.sym, 0, &player);
						break;
			}
		}

		screenRect.x = player.posX;
		screenRect.y = player.posY;

		/* Update du level, du joueur et des ennemies */

		updateLevel(&level, ecran);
		updatePlayerSprite(&player, &tempsPrecedent1, &tempsActuel1, &tempsPrecedent3, &tempsActuel3, &dammage);

		if(player.posX < 150 && player.posY > 410 && player.hostages != 0)
		{
			player.safeHostages += player.hostages;
			player.score += (player.hostages * 5);
			player.hostages = 0;
		}

		//Missiles
		missilesPlayer(&missiles, &player, ecran, &nbMissiles, &tempsPrecedent4, &tempsActuel4);

		//Tanks
		int apparition = tank_apparition(&player, &limitApparationTank);
		/*if(apparition == 1)
			tank_generation(&player, tanks, &nbTanks);*/
		tank_moving(tanks, &player, &nbTanks, &tempsPrecedent6, &tempsActuel6);

		//Planes
		apparition = plane_apparition(&player, &limitApparationPlane);
		if(apparition == 1)
			plane_generation(&player, planes, &nbPlanes);
		plane_moving(planes, &player, &nbPlanes, &tempsPrecedent11, &tempsActuel11);
		missilesPlanes(&planesMissiles, &player, &nbPlanesMissiles, &nbPlanes, &planes, &tempsPrecedent13, &tempsActuel13);

		//Saucers
		/*apparition = saucer_apparition(&player, &limitApparationSaucer, &nbMissiles);
		if(apparition == 1)
			saucer_generation(&player, saucers, &nbSaucers);*/
		saucer_moving(saucers, &player, &nbSaucers, &tempsPrecedent9, &tempsActuel9);

		int enemyRandomness = enemy_randomness(&level, &tempsPrecedent8, &tempsActuel8);
		if(player.posX >= 150)
		{
			switch(enemyRandomness)
			{
				case 0:
					tank_generation(&player, tanks, &nbTanks);
					break;
				case 1:
					plane_generation(&player, planes, &nbPlanes);
					break;
				case 2:
					saucer_generation(&player, saucers, &nbSaucers);
					break;
			}
		}

		/* COLLISIONS */

		collision(&hostages, &nbHostages, &buildings, &missiles, &planesMissiles, &tanks, &planes, &saucers, &player, &nbTanks, &nbPlanes, &nbSaucers, &nbMissiles, &nbPlanesMissiles, &tempsPrecedent7, &tempsActuel7, &tempsPrecedent10, &tempsActuel10, &tempsPrecedent12, &tempsActuel12, system);
		newHostage = collisionBuilding(&nbMissiles, &buildings, &missiles);
		if(newHostage < 5)
		{
			int buildingPosX = buildings[newHostage].position.x;
			hostages_generation(&buildingPosX, &hostages, &nbHostages);
			tank_generation(&player, tanks, &nbTanks);
		}
		hostages_moving(&hostages, &player, &nbHostages, &tempsPrecedent14, &tempsActuel14);

		/* BLITS */

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		SDL_BlitSurface(level.sprite->surface, level.sprite->rect, dynamicEvents, &dynamicRect);
		SDL_BlitSurface(rescueZone, NULL, level.sprite->surface, &positionRescueZone);
		SDL_BlitSurface(levelBuilding, NULL, level.sprite->surface, &positionLevelBuilding);

		/* Buildings */

		for(i=0;i<5;i++)
		{
			if(buildings[i].lifes == 0)
			{
				buildings[i].crop.x = 90;
				buildings[i].crop.y = 0;
			}
			SDL_BlitSurface(building, &buildings[i].crop, dynamicEvents, &buildings[i].position);
		}

		/* Hostages */

		for(i = 0; i < nbHostages; i++)
		{
			SDL_BlitSurface(hostage, &hostages[i].crop, dynamicEvents, &hostages[i].position);
		}

		/* Ennemies */

		//Planes
		for(i = 0; i < nbPlanes; i++)
		{
			SDL_BlitSurface(plane, &planes[i].crop, dynamicEvents, &planes[i].position);
		}

		//Saucers
		for(i = 0; i < nbSaucers; i++)
		{
			SDL_BlitSurface(saucer, &saucers[i].crop, dynamicEvents, &saucers[i].position);
		}

		/* Joueur */

		SDL_BlitSurface(player.sprite->surface, player.sprite->rect, dynamicEvents, &screenRect);

		//Tanks
		for(i = 0; i < nbTanks; i++)
		{
			SDL_BlitSurface(tank, &tanks[i].crop, dynamicEvents, &tanks[i].position);
		}

		/* Missiles */

		for(i = 0; i < nbMissiles; i++)
		{
			SDL_BlitSurface(missile, &missiles[i].crop, dynamicEvents, &missiles[i].position);
		}
		for(i = 0; i < nbPlanesMissiles; i++)
		{
			SDL_BlitSurface(planeMissile, &planesMissiles[i].crop, dynamicEvents, &planesMissiles[i].position);
		}

		/* Level */

		SDL_BlitSurface(dynamicEvents, level.sprite->rect, ecran, &dynamicRect);

		/* Infos de jeu */

		gameInfos(ecran, &player, &level, &tempsPrecedent2, &tempsActuel2);

		SDL_Flip(ecran);

		/* Fin du niveau */

		if(player.lifes == 0)
		{
			FMOD_Sound_Release(gameMainSound);
			if(player.posY > 410)
			{
				continuer = 0;
				newGame = gameover(ecran, system);
			}
		}
		if(player.score >= level.score && player.safeHostages >= level.hostages && player.posX < 150 && player.posY >= 410 && player.lifes != 0 && level.num != 11 && level.num != 12)
		{
			FMOD_Sound_Release(gameMainSound);
			continuer = 0;
			newGame = victory(ecran, system, &level);
		}
		if((player.score >= level.score && player.safeHostages >= level.hostages && player.posX < 150 && player.posY >= 410 && player.lifes != 0) && (level.num == 11 || level.num == 12))
		{
			FMOD_Sound_Release(gameMainSound);
			continuer = 0;
			newGame = 0;
			credits(ecran);
		}
    }

	/* FREE MEMORY */

	TTF_CloseFont(font);
    TTF_Quit();
    SDL_FreeSurface(player.sprite->surface);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(building);
    SDL_FreeSurface(dynamicEvents);
    SDL_FreeSurface(rescueZone);
    SDL_FreeSurface(levelBuilding);
    SDL_FreeSurface(missile);
    SDL_FreeSurface(tank);
    SDL_FreeSurface(plane);
    SDL_FreeSurface(saucer);
    SDL_FreeSurface(hostage);

    return newGame;
}




///////////////////////////////////////////////////////////////////////
//                                                                   //
//                       Other functions                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////




int titleScreen(SDL_Surface* screen, FMOD_SYSTEM* system)
{
    int continuer = 1, resultat;
    SDL_Surface *title = NULL, *buttonStartHover = NULL, *buttonQuitHover = NULL;
    SDL_Rect positionTitle, positionButtonQuit, positionButtonStart;
    SDL_Event event;
    FMOD_SOUND *titleScreen;
    FMOD_SOUND *choiceTitle;

    FMOD_System_CreateSound(system, "Sounds/titleScreen.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &titleScreen);
    FMOD_System_CreateSound(system, "Sounds/choiceTitle.wav", FMOD_CREATESAMPLE, 0, &choiceTitle);

    FMOD_Sound_SetLoopCount(titleScreen, -1);

    title = IMG_Load("graphism/background/title.png"); /* The Main Background */
    positionTitle.x = 0;
    positionTitle.y = 0;

    buttonStartHover = IMG_Load("graphism/buttons/buttonHover.png");
    positionButtonStart.x = 18;
    positionButtonStart.y = 420;

    buttonQuitHover = IMG_Load("graphism/buttons/buttonHover.png");
    positionButtonQuit.x = 143;
    positionButtonQuit.y = 420;

    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, titleScreen, 0, NULL);	/* Main Music (free rights): PeerGynt Lobogris - My Childhood Dream III */

    /* EVENT */

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        resultat = 0;
                        break;
                    case SDLK_F1:
                    	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, choiceTitle, 0, NULL); /* Play when you choose starting */
						continuer = 0;
                        break;
                    case SDLK_F10:
                        continuer = 0;
                        resultat = 0;
                        break;
                    default:
                        break;
                }
                break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.motion.y < 470 && event.motion.y > 420 && event.motion.x < 118 && event.motion.x > 18) /* Bouton START */
				{
					FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, choiceTitle, 0, NULL); /* Play when you choose starting */
					resultat = mdp(screen, &system, &choiceTitle);
					continuer = 0;
				}
				if(event.motion.y < 470 && event.motion.y > 420 && event.motion.x < 242 && event.motion.x > 143) /* Bouton QUIT */
				{
					continuer = 0;
					resultat = 0;
				}
				break;
			case SDL_QUIT:
                continuer = 0;
                resultat = 0;
                break;
            default:
                break;
        }

	/* BLITAGE */

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(title, NULL, screen, &positionTitle);

        if(event.motion.y < 470 && event.motion.y > 420 && event.motion.x < 118 && event.motion.x > 18)
		{
			SDL_BlitSurface(buttonStartHover, NULL, screen, &positionButtonStart); /* Blit when the button START is hover */
		}
		if(event.motion.y < 470 && event.motion.y > 420 && event.motion.x < 242 && event.motion.x > 143)
		{
			SDL_BlitSurface(buttonQuitHover, NULL, screen, &positionButtonQuit); /* Blit when the button QUIT is hover */
		}

        SDL_Flip(screen);
    }

	/* FREE MEMORY */

	FMOD_Sound_Release(titleScreen);
	FMOD_Sound_Release(choiceTitle);
	return resultat;
}

int victory(SDL_Surface* screen, FMOD_SYSTEM* system, Level* level)
{
    int continuer = 1, resultat;
    SDL_Surface *background = NULL, *password = NULL;
    SDL_Rect positionBackground, positionPassword;
    SDL_Event event;
    FMOD_SOUND *victory;
    FMOD_System_CreateSound(system, "Sounds/victory.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &victory);
    FMOD_Sound_SetLoopCount(victory, -1);

	TTF_Init();
    TTF_Font *font = NULL;
    font = TTF_OpenFont("graphism/police/unispace.ttf", 30);
    SDL_Color white = {255, 255, 255};

    switch(level->num)
    {
		case 1:
			password = TTF_RenderText_Blended(font, "helicopter", white);
			break;
		case 2:
			password = TTF_RenderText_Blended(font, "gladiators", white);
			break;
		case 3:
			password = TTF_RenderText_Blended(font, "explosions", white);
			break;
		case 4:
			password = TTF_RenderText_Blended(font, "mastodonic", white);
			break;
		case 5:
			password = TTF_RenderText_Blended(font, "hellbender", white);
			break;
		case 6:
			password = TTF_RenderText_Blended(font, "weaknesses", white);
			break;
		case 7:
			password = TTF_RenderText_Blended(font, "zombifying", white);
			break;
		case 8:
			password = TTF_RenderText_Blended(font, "supernovas", white);
			break;
		case 9:
			password = TTF_RenderText_Blended(font, "overkilled", white);
			break;
		case 10:
			password = TTF_RenderText_Blended(font, "ultradeath", white);
			break;
    }

    positionPassword.x = 320;
	positionPassword.y = 410;

    background = IMG_Load("graphism/background/victory.png");
    positionBackground.x = 0;
    positionBackground.y = 0;

    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, victory, 0, NULL);

    /* EVENT */

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        continuer = 0;
                        resultat = 2;
                        break;
                    case SDLK_KP_ENTER:
                    	continuer = 0;
                    	resultat = 2;
                        break;
                    default:
                        break;
                }
                break;
			case SDL_QUIT:
                continuer = 0;
                resultat = 0;
                break;
            default:
                break;
        }

	/* BLITAGE */

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(background, NULL, screen, &positionBackground);
        SDL_BlitSurface(password, NULL, screen, &positionPassword);
        SDL_Flip(screen);
    }

	/* FREE MEMORY */

	TTF_CloseFont(font);
    TTF_Quit();
	SDL_FreeSurface(background);
	SDL_FreeSurface(password);
	FMOD_Sound_Release(victory);
	return resultat;
}

int gameover(SDL_Surface* screen, FMOD_SYSTEM* system)
{
    int continuer = 1, resultat;
    SDL_Surface *background = NULL, *buttonStartHover = NULL, *buttonQuitHover = NULL;
    SDL_Rect positionBackground, positionButtonQuit, positionButtonStart;
    SDL_Event go;
    FMOD_SOUND *gameoverSound;

    FMOD_System_CreateSound(system, "Sounds/gameOver.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &gameoverSound);
    FMOD_Sound_SetLoopCount(gameover, -1);

    background = IMG_Load("graphism/background/gameover.png");
    positionBackground.x = 0;
    positionBackground.y = 0;

    buttonStartHover = IMG_Load("graphism/buttons/buttonHover.png");
    positionButtonStart.x = 40;
    positionButtonStart.y = 389;

    buttonQuitHover = IMG_Load("graphism/buttons/buttonHover.png");
    positionButtonQuit.x = 190;
    positionButtonQuit.y = 389;

    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, gameoverSound, 0, NULL);

    /* EVENT */

    while (continuer)
    {
        SDL_PollEvent(&go);
        switch(go.type)
        {
			case SDL_MOUSEBUTTONDOWN:
				if(go.motion.y < 439 && go.motion.y > 389 && go.motion.x < 140 && go.motion.x > 40)
				{
					resultat = 1;
					continuer = 0;
				}
				if(go.motion.y < 439 && go.motion.y > 389 && go.motion.x < 290 && go.motion.x > 190)
				{
					continuer = 0;
					resultat = 0;
				}
				break;
			case SDL_QUIT:
                continuer = 0;
                resultat = 0;
                break;
            default:
                break;
        }

	/* BLITAGE */

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(background, NULL, screen, &positionBackground);
        if(go.motion.y < 439 && go.motion.y > 389 && go.motion.x < 140 && go.motion.x > 40)
		{
			SDL_BlitSurface(buttonStartHover, NULL, screen, &positionButtonStart);
		}
		if(go.motion.y < 439 && go.motion.y > 389 && go.motion.x < 290 && go.motion.x > 190)
		{
			SDL_BlitSurface(buttonQuitHover, NULL, screen, &positionButtonQuit);
		}

        SDL_Flip(screen);
    }

	/* FREE MEMORY */

	FMOD_Sound_Release(gameoverSound);
	SDL_FreeSurface(background);
	return resultat;
}


void handleKey(SDLKey key, int state, Player* player) // Prise en charge des touches
{
	switch(key)
	{
		/* Player */

		case SDLK_w:
            if(state != 0)
            {
                player->moveStageY = MOVE_UP;
            }
            else
            {
                player->moveStageY = MOVE_IDLE;
            }
             if(player->moveDirection != MOVE_TOLEFT && player->moveDirection != MOVE_TORIGHT)
                player->moveDirection = MOVE_TOFACE;
			break;
		case SDLK_s:
            if(state != 0)
                player->moveStageY = MOVE_DOWN;
            else

                player->moveStageY = MOVE_IDLE;
            if(player->moveDirection != MOVE_TOLEFT && player->moveDirection != MOVE_TORIGHT)
                player->moveDirection = MOVE_TOFACE;
			break;
		case SDLK_a:
             if(state != 0)
             {
                player->moveStageX = MOVE_LEFT;
                player->moveDirection = MOVE_TOLEFT;
            }
            else
            {
                player->moveStageX = MOVE_IDLE;
                player->moveDirection = MOVE_TOLEFTIDLE;
            }
			break;
		case SDLK_d:
            if(state != 0)
             {
                player->moveStageX = MOVE_RIGHT;
                player->moveDirection = MOVE_TORIGHT;
            }
            else
            {
                player->moveStageX = MOVE_IDLE;
                player->moveDirection = MOVE_TORIGHTIDLE;
            }
			break;
        case SDLK_RCTRL:

            break;
        case SDLK_LCTRL:

            break;
        default:
            break;
	}
}


int mdp(SDL_Surface* screen, FMOD_SYSTEM* system, FMOD_SOUND* choiceTitle)
{
	/* VARIABLES */

	SDL_Surface *background = NULL, *buttonSendHover = NULL, *buttonLvl1Hover = NULL, *texte = NULL;
    SDL_Rect positionBackground, positionButtonSend, positionButtonLvl1, positionText;
    SDL_Event event;
    TTF_Init();
    TTF_Font *police = NULL;
	police = TTF_OpenFont("graphism/police/unispace.ttf", 25);
    SDL_Color white = {255, 255, 255};



	char mdpUser[11] = {".........."};

	char mdpLvl2[10] = {"helicopter"};
	char mdpLvl3[10] = {"gladiators"};
	char mdpLvl4[10] = {"explosions"};
	char mdpLvl5[10] = {"mastodonic"};
	char mdpLvl6[10] = {"hellbender"};
	char mdpLvl7[10] = {"weaknesses"};
	char mdpLvl8[10] = {"zombifying"};
	char mdpLvl9[10] = {"supernovas"};
	char mdpLvl10[10] = {"overkilled"};
	char mdpLvl11[10] = {"ultradeath"};
	char mdpLvl12[10] = {"trolololol"};

	int lvl = 0; // Importante variable déterminant beaucoup de paramètres
    int continuer = 1;
    int i, j;
    int validMdp = 0;

    background = IMG_Load("graphism/background/backgroundMdp.png"); // The Main Background
    positionBackground.x = 0;
    positionBackground.y = 0;

    buttonSendHover = IMG_Load("graphism/buttons/buttonHover.png");
    positionButtonSend.x = 18;
    positionButtonSend.y = 420;

    buttonLvl1Hover = IMG_Load("graphism/buttons/buttonHover.png");
    positionButtonLvl1.x = 143;
    positionButtonLvl1.y = 420;

    texte = TTF_RenderText_Blended(police, mdpUser, white);
    positionText.x = 235;
    positionText.y = 190;

	/* EVENT */
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				if(validMdp != 10)
				{
					switch(event.key.keysym.sym) //Gestion des touches par ttf.
					{
							case SDLK_a:
								mdpUser[validMdp] = 'q';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_b:
								mdpUser[validMdp] = 'b';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_c:
								mdpUser[validMdp] = 'c';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_d:
								mdpUser[validMdp] = 'd';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_e:
								mdpUser[validMdp] = 'e';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_f:
								mdpUser[validMdp] = 'f';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_g:
								mdpUser[validMdp] = 'g';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_h:
								mdpUser[validMdp] = 'h';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_i:
								mdpUser[validMdp] = 'i';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_j:
								mdpUser[validMdp] = 'j';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_k:
								mdpUser[validMdp] = 'k';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_l:
								mdpUser[validMdp] = 'l';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_n:
								mdpUser[validMdp] = 'n';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_o:
								mdpUser[validMdp] = 'o';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_p:
								mdpUser[validMdp] = 'p';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_q:
								mdpUser[validMdp] = 'a';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_r:
								mdpUser[validMdp] = 'r';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_s:
								mdpUser[validMdp] = 's';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_t:
								mdpUser[validMdp] = 't';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_u:
								mdpUser[validMdp] = 'u';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_v:
								mdpUser[validMdp] = 'v';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_w:
								mdpUser[validMdp] = 'z';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_x:
								mdpUser[validMdp] = 'x';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_y:
								mdpUser[validMdp] = 'y';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_z:
								mdpUser[validMdp] = 'w';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							case SDLK_SEMICOLON:
								mdpUser[validMdp] = 'm';
								validMdp ++;
								texte = TTF_RenderText_Blended(police, mdpUser, white);
								break;
							default:
								break;
					}
				}
				else
				{
					for(i=0; i<10; i++)
					{
						mdpUser[i] = '.';
						texte = TTF_RenderText_Blended(police, mdpUser, white);
					}
					validMdp = 0;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.motion.y < 470 && event.motion.y > 420 && event.motion.x < 118 && event.motion.x > 18) // Bouton SEND
				{
					FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, choiceTitle, 0, NULL);
					for(i=0; i<11; i++)
					{
						switch(i)
						{
							case 0:
								for(j=0; j<10; j++)
								{
									if(mdpUser[j] == mdpLvl2[j])
									{
										lvl = 2;
										continuer = 0;
									}
									else
									{
										lvl = 0;
										continuer = 1;
										break;
									}
								}
								break;
							case 1:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl3[j])
								{
									lvl = 3;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 2:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl4[j])
								{
									lvl = 4;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 3:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl5[j])
								{
									lvl = 5;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 4:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl6[j])
								{
									lvl = 6;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 5:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl7[j])
								{
									lvl = 7;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 6:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl8[j])
								{
									lvl = 8;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 7:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl9[j])
								{
									lvl = 9;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 8:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl10[j])
								{
									lvl = 10;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 9:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl11[j])
								{
									lvl = 11;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							case 10:
							for(j=0; j<10; j++)
							{
								if(mdpUser[j] == mdpLvl12[j])
								{
									lvl = 12;
									continuer = 0;
								}
								else
								{
									lvl = 0;
									continuer = 1;
									break;
								}
							}
								break;
							default:
								break;
						}
						if(lvl != 0)
						{
							break;
						}
					}
					validMdp = 0;
					for(i=0; i<10; i++)
					{
						mdpUser[i] = '.';
						texte = TTF_RenderText_Blended(police, mdpUser, white);
					}
				}
				if(event.motion.y < 470 && event.motion.y > 420 && event.motion.x < 242 && event.motion.x > 143) // Bouton LVL1
				{
					FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, choiceTitle, 0, NULL);
					lvl = 1;
					continuer = 0;
				}
				break;
			case SDL_QUIT:
                continuer = 0;
                lvl = 0;
                break;
		}

	/* BLITAGE */

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(background, NULL, screen, &positionBackground);
		SDL_BlitSurface(texte, NULL, screen, &positionText); // Blit of the text

        if(event.motion.y < 470 && event.motion.y > 420 && event.motion.x < 118 && event.motion.x > 18)
		{
			SDL_BlitSurface(buttonSendHover, NULL, screen, &positionButtonSend); // Blit when the button SEND is hover
		}
		if(event.motion.y < 470 && event.motion.y > 420 && event.motion.x < 242 && event.motion.x > 143)
		{
			SDL_BlitSurface(buttonLvl1Hover, NULL, screen, &positionButtonLvl1); // Blit when the button LVL1 is hover
		}

        SDL_Flip(screen);
	}

	/* FREE MEMORY */

	TTF_CloseFont(police);
	TTF_Quit();
	SDL_FreeSurface(texte);
	SDL_FreeSurface(buttonSendHover);
	SDL_FreeSurface(buttonLvl1Hover);
    SDL_FreeSurface(background);

    return lvl;
}

void outputLog(const char* logStr)
{
    FILE* log = fopen("logs.txt", "a");
    if(log != NULL)
    {
        fprintf(log, "%s \r\n", logStr);
        fflush(log);
        fclose(log);
    }
}

int random_range (int min, int max)
{
    int result = rand() % (max-min) + min;
    char* buffer[5];
    sprintf(buffer, "%d", result);
    outputLog((const)buffer);
    return result;
}

void gameInfos (SDL_Surface* screen, Player* player, Level* level, int* tempsPrecedent2, int* tempsActuel2)
{
	SDL_Surface *text1, *text2, *text3 = NULL, *timer = NULL, *lifes = NULL, *score = NULL, *hostages = NULL;
	SDL_Rect positionText1, positionText2, positionText3, positionTimer, positionLifes, positionScore, positionHostages;
	TTF_Init();
    TTF_Font *police = NULL;
	police = TTF_OpenFont("graphism/police/unispace.ttf", 15);
    SDL_Color white = {255, 255, 255};
    SDL_Color green = {0, 255, 0};


    int i;
    char* cTime[5];
    char* cScore[5];
    char* cHostages[5];

    sprintf(cTime, "%d", level->chrono);
    sprintf(cScore, "%d", player->score);
    sprintf(cHostages, "%d", player->safeHostages);

	*tempsActuel2 = SDL_GetTicks();
	if ((*tempsActuel2 - *tempsPrecedent2 > 1000) && level->chrono != 0)
	{
		level->chrono --;
		sprintf(cTime, "%d", level->chrono);
		*tempsPrecedent2 = *tempsActuel2;
	}
	if (level->chrono == 0)
	{
		player->lifes = 0;
	}

	text1 = TTF_RenderText_Blended(police, "[TIME]", white);
	positionText1.x = 5;
	positionText1.y = 5;

	timer = TTF_RenderText_Blended(police, cTime, white);
	positionTimer.x = 65;
	positionTimer.y = 5;

	if(player->score >= level->score)
	{
		score = TTF_RenderText_Blended(police, cScore, green);
		text2 = TTF_RenderText_Blended(police, "[SCORE]", green);
	}
	else
	{
		score = TTF_RenderText_Blended(police, cScore, white);
		text2 = TTF_RenderText_Blended(police, "[SCORE]", white);
	}

	positionText2.x = 450;
    positionText2.y = 5;
	positionScore.x = 525;
    positionScore.y = 5;

	if(player->safeHostages >= level->hostages)
	{
		text3 = TTF_RenderText_Blended(police, "[HOSTAGES]", green);
		hostages = TTF_RenderText_Blended(police, cHostages, green);
	}
	else
	{
		text3 = TTF_RenderText_Blended(police, "[HOSTAGES]", white);
		hostages = TTF_RenderText_Blended(police, cHostages, white);
	}

	positionText3.x = 200;
    positionText3.y = 5;
	positionHostages.x = 305;
    positionHostages.y = 5;

    positionLifes.x = 5;
    positionLifes.y = 450;
    switch(player->lifes)
    {
		case 3:
			lifes = IMG_Load("Sprites/Heli/lifes3.png");
			SDL_BlitSurface(lifes, NULL, screen, &positionLifes); // Blit of the lifes
			break;
		case 2:
			lifes = IMG_Load("Sprites/Heli/lifes2.png");
			SDL_BlitSurface(lifes, NULL, screen, &positionLifes); // Blit of the lifes
			break;
		case 1:
			lifes = IMG_Load("Sprites/Heli/lifes1.png");
			SDL_BlitSurface(lifes, NULL, screen, &positionLifes); // Blit of the lifes
			break;
		case 0:
			lifes = IMG_Load("Sprites/Heli/lifes0.png");
			SDL_BlitSurface(lifes, NULL, screen, &positionLifes); // Blit of the lifes
			break;
		default:
			break;
    }

    SDL_BlitSurface(timer, NULL, screen, &positionTimer); // Blit of the timer
    SDL_BlitSurface(text1, NULL, screen, &positionText1); // Blit of the timer
    SDL_BlitSurface(score, NULL, screen, &positionScore); // Blit of the score
    SDL_BlitSurface(text2, NULL, screen, &positionText2); // Blit of the score
    SDL_BlitSurface(hostages, NULL, screen, &positionHostages); // Blit of hostages
    SDL_BlitSurface(text3, NULL, screen, &positionText3); // Blit of hostages


    TTF_CloseFont(police);
	TTF_Quit();
	SDL_FreeSurface(timer);
	SDL_FreeSurface(score);
	SDL_FreeSurface(lifes);
	SDL_FreeSurface(hostages);
	SDL_FreeSurface(text1);
	SDL_FreeSurface(text2);
	SDL_FreeSurface(text3);
}

int transition(SDL_Surface* screen)
{
    int resultat;
    int tempsPrecedent = 0, tempsActuel = 0;
    SDL_Surface *heli = NULL;
    SDL_Rect positionHeli;

    heli = IMG_Load("Sprites/Heli/heli.gif");
	SDL_SetColorKey(heli, SDL_SRCCOLORKEY, SDL_MapRGB(heli->format, 9, 113, 255));

    positionHeli.x = -38;
    positionHeli.y = 225;

    do
	{
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 3)
		{
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			SDL_BlitSurface(heli, NULL, screen, &positionHeli);
			SDL_Flip(screen);
			positionHeli.x += 1;
			tempsPrecedent = tempsActuel;
		}
	}
	while(positionHeli.x < 640);

	resultat = 1;

	/* FREE MEMORY */

	SDL_FreeSurface(heli);
	return resultat;
}

void intro(SDL_Surface* screen, FMOD_SYSTEM* system)
{
    int tempsActuel = 0;
    int temp = 0;
    SDL_Surface *background = NULL;
    SDL_Rect positionBackground;
	FMOD_SOUND *oww;
    FMOD_System_CreateSound(system, "Sounds/oww.ogg", FMOD_CREATESAMPLE, 0, &oww);

    background = IMG_Load("graphism/background/oww.png");

    positionBackground.x = 0;
    positionBackground.y = 0;

    do
	{
		tempsActuel = SDL_GetTicks();
		if (tempsActuel > 500 && temp == 0)
		{
			FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, oww, 0, NULL);
			temp = 1;
		}
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(background, NULL, screen, &positionBackground);
		SDL_Flip(screen);
	}
	while(tempsActuel < 1500);


	/* FREE MEMORY */

	FMOD_Sound_Release(oww);
	SDL_FreeSurface(background);
}

void credits(SDL_Surface* screen)
{
    int tempsActuel = 0, tempsPrecedent = 0;
    SDL_Surface *background = NULL;
    SDL_Rect positionBackground;

    background = IMG_Load("graphism/background/credits.png");

    positionBackground.x = 0;
    positionBackground.y = 0;
	tempsPrecedent = SDL_GetTicks();

    do
	{
		tempsActuel = SDL_GetTicks();
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(background, NULL, screen, &positionBackground);
		SDL_Flip(screen);
	}
	while(tempsActuel - tempsPrecedent < 8000);


	/* FREE MEMORY */

	SDL_FreeSurface(background);
}

