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
#include "../Headers/dial.h"
#include <windows.h>
//#inlude <SDL/sdlgfx.h>



int main(int argc, char* argv[])
{
    outputLog("MAIN_ENTER");

	/* Définition des variables */

	SDL_Surface *ecran = NULL;

	FMOD_SYSTEM *system;

	int lvl; // Numéro du level exécuté
	int newGame = 0; // Pour rejouer une partie


	/*Initialisation de la SDL */

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("The HeliUpper", NULL);
    HICON chopIcon = (HICON) LoadImage(GetModuleHandle(NULL), "graphism/ico/icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	HWND mainWnd = FindWindow(NULL, "The HeliUpper");
	SendMessage(mainWnd, WM_SETICON, ICON_BIG, (LPARAM)chopIcon);

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL);

	intro(ecran, system);
    lvl = titleScreen(ecran, system);
    if(lvl != 0)
	{
		do
		{
			transition(ecran);
			dialog(ecran, system, &lvl);
			transition(ecran);
			newGame = gameLoop(ecran, system, &lvl);
			if(newGame == 2)
			{
				lvl ++;
			}
		}
		while(newGame > 0);
	}

	/* Désactivation de la SDL */

	SDL_FreeSurface(ecran);
	IMG_Quit();
	FMOD_System_Close(system);
	FMOD_System_Release(system);

	return 0;
}
