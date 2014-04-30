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
#include "../Headers/dial.h"
#include <windows.h>



int dialog (SDL_Surface *screen, FMOD_SYSTEM* system, int* lvl)
{
    int continuer = 1;

    SDL_Surface *background = NULL, *levelInfos = NULL, *time = NULL, *score = NULL, *hostages = NULL, *l1= NULL, *l2= NULL, *l3= NULL, *l4= NULL, *l5= NULL, *l6= NULL, *l7= NULL, *l8= NULL;
    SDL_Rect positionBackground, positionLevelInfos, positionTime, positionScore, positionHostages, positionL1, positionL2, positionL3, positionL4, positionL5, positionL6, positionL7, positionL8;
    SDL_Event event;

    FMOD_SOUND *dialSound;
    FMOD_System_CreateSound(system, "Sounds/slipspace.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL, 0, &dialSound);
    FMOD_Sound_SetLoopCount(dialSound, -1);

    TTF_Init();
    TTF_Font *font = NULL;
    TTF_Font *num = NULL;
    TTF_Font *infos = NULL;
    font = TTF_OpenFont("graphism/police/unispace.ttf", 15);
    num = TTF_OpenFont("graphism/police/unispace.ttf", 33);
    infos = TTF_OpenFont("graphism/police/unispace.ttf", 10);
    SDL_Color maduro = {57, 47, 35};


	switch(*lvl)
	{
		case 1:
			levelInfos = TTF_RenderText_Blended(num, "[1]", maduro);
			time = TTF_RenderText_Blended(infos, "180", maduro);
			score = TTF_RenderText_Blended(infos, "200", maduro);
			hostages = TTF_RenderText_Blended(infos, "32", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "Hey ! You must be new, no ? In this case,", maduro);
			l2 = TTF_RenderText_Blended(font, "let me tell you some advices about your", maduro);
			l3 = TTF_RenderText_Blended(font, "war machine called the HeliUpper. Use the", maduro);
			l4 = TTF_RenderText_Blended(font, "force padawan ! I mean ZQSD and you will", maduro);
			l5 = TTF_RenderText_Blended(font, "control the sky ! For taking fire on your", maduro);
			l6 = TTF_RenderText_Blended(font, "enemies, just press OPLM or SPACE.", maduro);
			l7 = TTF_RenderText_Blended(font, "And look at the bottom, you must complete", maduro);
			l8 = TTF_RenderText_Blended(font, "those objectives, so go rescue them all !", maduro);
			break;
		case 2:
			levelInfos = TTF_RenderText_Blended(num, "[2]", maduro);
			time = TTF_RenderText_Blended(infos, "180", maduro);
			score = TTF_RenderText_Blended(infos, "400", maduro);
			hostages = TTF_RenderText_Blended(infos, "32", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "You were very impressive last day, little", maduro);
			l2 = TTF_RenderText_Blended(font, "beatle ! But the wolrd isn't the same", maduro);
			l3 = TTF_RenderText_Blended(font, "anymore and the night is dark and full of", maduro);
			l4 = TTF_RenderText_Blended(font, "terrors. I mean full of tanks, planes and", maduro);
			l5 = TTF_RenderText_Blended(font, "flying saucers. But if you succeed to", maduro);
			l6 = TTF_RenderText_Blended(font, "this level [2], I'll tell you some triks", maduro);
			l7 = TTF_RenderText_Blended(font, "and you will be able to raining fire upon", maduro);
			l8 = TTF_RenderText_Blended(font, "their sons of a bit, go get'em !", maduro);
			break;
		case 3:
			levelInfos = TTF_RenderText_Blended(num, "[3]", maduro);
			time = TTF_RenderText_Blended(infos, "180", maduro);
			score = TTF_RenderText_Blended(infos, "400", maduro);
			hostages = TTF_RenderText_Blended(infos, "40", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "HoOOo, they get served ! No one is", maduro);
			l2 = TTF_RenderText_Blended(font, "strong enough to resist HeliUpper.", maduro);
			l3 = TTF_RenderText_Blended(font, "So listen, it appears that ennemies come", maduro);
			l4 = TTF_RenderText_Blended(font, "randomly to you but you're protect when", maduro);
			l5 = TTF_RenderText_Blended(font, "you are in the rescue zone.", maduro);
			l6 = TTF_RenderText_Blended(font, "And if you're high in the sky, planes", maduro);
			l7 = TTF_RenderText_Blended(font, "show up, if you low to the ground, they", maduro);
			l8 = TTF_RenderText_Blended(font, "are the tanks. So smart you need to be.", maduro);
			break;
		case 4:
			levelInfos = TTF_RenderText_Blended(num, "[4]", maduro);
			time = TTF_RenderText_Blended(infos, "220", maduro);
			score = TTF_RenderText_Blended(infos, "500", maduro);
			hostages = TTF_RenderText_Blended(infos, "48", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "Arghh, more people are prisoner everydays", maduro);
			l2 = TTF_RenderText_Blended(font, "and the difficuty increase. You've talent", maduro);
			l3 = TTF_RenderText_Blended(font, "and my dear sweet helicopter trust in you", maduro);
			l4 = TTF_RenderText_Blended(font, "so you're named as captain. So captain my", maduro);
			l5 = TTF_RenderText_Blended(font, "captain, let's detroy all the tanks,", maduro);
			l6 = TTF_RenderText_Blended(font, "let's burn all the planes and saucers,", maduro);
			l7 = TTF_RenderText_Blended(font, "let's crucify all the bieber's fans !!", maduro);
			l8 = TTF_RenderText_Blended(font, "THIS IS SPAAAAARTAAA !!!", maduro);
			break;
		case 5:
			levelInfos = TTF_RenderText_Blended(num, "[5]", maduro);
			time = TTF_RenderText_Blended(infos, "60", maduro);
			score = TTF_RenderText_Blended(infos, "300", maduro);
			hostages = TTF_RenderText_Blended(infos, "16", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "Good job on you last mission Captain !", maduro);
			l2 = TTF_RenderText_Blended(font, "This time, you're need to be tricky.", maduro);
			l3 = TTF_RenderText_Blended(font, "You're time is short and hostages are in", maduro);
			l4 = TTF_RenderText_Blended(font, "numbers. Yes, I'll make a diversion and", maduro);
			l5 = TTF_RenderText_Blended(font, "you'll have only one minute to save them", maduro);
			l6 = TTF_RenderText_Blended(font, "from the grief of the terrible Bowser.", maduro);
			l7 = TTF_RenderText_Blended(font, "May the force be with you Captain", maduro);
			l8 = TTF_RenderText_Blended(font, "and after that, I'll pay you a Slurm.", maduro);
			break;
		case 6:
			levelInfos = TTF_RenderText_Blended(num, "[6]", maduro);
			time = TTF_RenderText_Blended(infos, "240", maduro);
			score = TTF_RenderText_Blended(infos, "500", maduro);
			hostages = TTF_RenderText_Blended(infos, "50", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "You've made it at time captain, good game.", maduro);
			l2 = TTF_RenderText_Blended(font, "And I've heard that you've named the", maduro);
			l3 = TTF_RenderText_Blended(font, "chopper Pidgeon. It's a good dog that", maduro);
			l4 = TTF_RenderText_Blended(font, "one. So this time, Roucoups and you are", maduro);
			l5 = TTF_RenderText_Blended(font, "trying to rescue some hostages for change", maduro);
			l6 = TTF_RenderText_Blended(font, "but difficulty will be there waiting for", maduro);
			l7 = TTF_RenderText_Blended(font, "you. Be sure that you're always in time", maduro);
			l8 = TTF_RenderText_Blended(font, "and bring back people in all pieces.", maduro);
			break;
		case 7:
			levelInfos = TTF_RenderText_Blended(num, "[7]", maduro);
			time = TTF_RenderText_Blended(infos, "300", maduro);
			score = TTF_RenderText_Blended(infos, "700", maduro);
			hostages = TTF_RenderText_Blended(infos, "56", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "Sorry I'm on strike today.", maduro);
			l2 = TTF_RenderText_Blended(font, "Go buy a poney to replace me, I'm looking", maduro);
			l3 = TTF_RenderText_Blended(font, "oggy and the cockroaches on TV.", maduro);
			l4 = TTF_RenderText_Blended(font, "No I'm kidding ! Evil doesn't wait Captain", maduro);
			l5 = TTF_RenderText_Blended(font, "and you need to focus on the mission !", maduro);
			l6 = TTF_RenderText_Blended(font, "Go kick them in the nuts because they", maduro);
			l7 = TTF_RenderText_Blended(font, "deserve it and show them the strengh of", maduro);
			l8 = TTF_RenderText_Blended(font, "the hammer of Thor !", maduro);
			break;
		case 8:
			levelInfos = TTF_RenderText_Blended(num, "[8]", maduro);
			time = TTF_RenderText_Blended(infos, "190", maduro);
			score = TTF_RenderText_Blended(infos, "400", maduro);
			hostages = TTF_RenderText_Blended(infos, "64", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "You're now a veterant Captain, you've made", maduro);
			l2 = TTF_RenderText_Blended(font, "you named on the battlefield and many", maduro);
			l3 = TTF_RenderText_Blended(font, "super vilains know you are. But beware", maduro);
			l4 = TTF_RenderText_Blended(font, "because the dark side have cookies and", maduro);
			l5 = TTF_RenderText_Blended(font, "my ex partener fall in their trick.", maduro);
			l6 = TTF_RenderText_Blended(font, "He didn't make it...", maduro);
			l7 = TTF_RenderText_Blended(font, "So for tribute of this great guy, let's", maduro);
			l8 = TTF_RenderText_Blended(font, "clame his name and own all enemies !!", maduro);
			break;
		case 9:
			levelInfos = TTF_RenderText_Blended(num, "[9]", maduro);
			time = TTF_RenderText_Blended(infos, "140", maduro);
			score = TTF_RenderText_Blended(infos, "440", maduro);
			hostages = TTF_RenderText_Blended(infos, "72", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "Enemies's strengh are weak everyday and", maduro);
			l2 = TTF_RenderText_Blended(font, "it's thanks to you. You built an area", maduro);
			l3 = TTF_RenderText_Blended(font, "of peace in Gottham city, the area of", maduro);
			l4 = TTF_RenderText_Blended(font, "UpperMan. You are legion, you are legend", maduro);
			l5 = TTF_RenderText_Blended(font, "and you sattle a bird bird called Pidgeon", maduro);
			l6 = TTF_RenderText_Blended(font, "so, it's kind of classy.", maduro);
			l7 = TTF_RenderText_Blended(font, "But you need to continue, evil may", maduro);
			l8 = TTF_RenderText_Blended(font, "reserved some suprise to you.", maduro);
			break;
		case 10:
			levelInfos = TTF_RenderText_Blended(num, "[10]", maduro);
			time = TTF_RenderText_Blended(infos, "240", maduro);
			score = TTF_RenderText_Blended(infos, "750", maduro);
			hostages = TTF_RenderText_Blended(infos, "72", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "UpperMan ! Godzilla will attack the city", maduro);
			l2 = TTF_RenderText_Blended(font, "int 360 secondes ! You need to rescue all", maduro);
			l3 = TTF_RenderText_Blended(font, "of them or they will be crush in a giant", maduro);
			l4 = TTF_RenderText_Blended(font, "fantasist dinosaur living in the sea !", maduro);
			l5 = TTF_RenderText_Blended(font, "Difficulty is hard, I know... But it's", maduro);
			l6 = TTF_RenderText_Blended(font, "possible, all is possible with Kim", maduro);
			l7 = TTF_RenderText_Blended(font, "Possilbe ! And don't forget:", maduro);
			l8 = TTF_RenderText_Blended(font, "Where will wants not, a way opens.", maduro);
			break;
		case 11:
			levelInfos = TTF_RenderText_Blended(num, "[FINAL]", maduro);
			time = TTF_RenderText_Blended(infos, "200", maduro);
			score = TTF_RenderText_Blended(infos, "800", maduro);
			hostages = TTF_RenderText_Blended(infos, "80", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "Congratulations, you're in the final step", maduro);
			l2 = TTF_RenderText_Blended(font, "and you know, drugs are bad mmkay. But", maduro);
			l3 = TTF_RenderText_Blended(font, "it's been fun to play with you and you're", maduro);
			l4 = TTF_RenderText_Blended(font, "nicely bird. I hope that you will pass", maduro);
			l5 = TTF_RenderText_Blended(font, "trough the fire and flammes. It will not", maduro);
			l6 = TTF_RenderText_Blended(font, "be easy for you.", maduro);
			l7 = TTF_RenderText_Blended(font, "Goodbye Captain ! Goodby UpperMan !", maduro);
			l8 = TTF_RenderText_Blended(font, "Live long and prosper.", maduro);
			break;
		case 12:
			levelInfos = TTF_RenderText_Blended(num, "[BONUS]", maduro);
			time = TTF_RenderText_Blended(infos, "666", maduro);
			score = TTF_RenderText_Blended(infos, "30000", maduro);
			hostages = TTF_RenderText_Blended(infos, "80", maduro);
		  //l1 = TTF_RenderText_Blended(font, ".........................................", black); LONGUEUR D'UNE LIGNE
			l1 = TTF_RenderText_Blended(font, "Oh ! You discover the bonus level ?", maduro);
			l2 = TTF_RenderText_Blended(font, "Nothing is logicle here so enjoy !", maduro);
			l3 = TTF_RenderText_Blended(font, "But be carreful to enemies, they're Crazy", maduro);
			l4 = TTF_RenderText_Blended(font, "and in a really large, very, very, very", maduro);
			l5 = TTF_RenderText_Blended(font, "large number.", maduro);
			l6 = TTF_RenderText_Blended(font, "So, welcome to the oblivion of the code", maduro);
			l7 = TTF_RenderText_Blended(font, "source captain. Don't panic on board !", maduro);
			l8 = TTF_RenderText_Blended(font, "The fun and the speedness before !", maduro);
			break;
	}

	positionLevelInfos.x = 315;
	positionLevelInfos.y = 94;

	positionTime.x = 216;
	positionTime.y = 323;

	positionScore.x = 236;
	positionScore.y = 338;

	positionHostages.x = 266;
	positionHostages.y = 352;

    positionL1.x = 164;
    positionL1.y = 150;
    positionL2.x = 164;
    positionL2.y = 170;
    positionL3.x = 164;
    positionL3.y = 190;
    positionL4.x = 164;
    positionL4.y = 210;
    positionL5.x = 164;
    positionL5.y = 230;
    positionL6.x = 164;
    positionL6.y = 250;
    positionL7.x = 164;
    positionL7.y = 270;
    positionL8.x = 164;
    positionL8.y = 290;

    background = IMG_Load("graphism/background/dial.png");
    positionBackground.x = 0;
    positionBackground.y = 0;

    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, dialSound, 0, NULL);

    /* EVENT */

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
			case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                        continuer = 0;
                        break;
					case SDLK_RETURN:
                        continuer = 0;
                        break;
					default:
						break;
                }
				break;
            default:
                break;
        }

	/* BLITAGE */

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(background, NULL, screen, &positionBackground);
        SDL_BlitSurface(levelInfos, NULL, screen, &positionLevelInfos);
        SDL_BlitSurface(time, NULL, screen, &positionTime);
        SDL_BlitSurface(score, NULL, screen, &positionScore);
        SDL_BlitSurface(hostages, NULL, screen, &positionHostages);
        SDL_BlitSurface(l1, NULL, screen, &positionL1);
        SDL_BlitSurface(l2, NULL, screen, &positionL2);
        SDL_BlitSurface(l3, NULL, screen, &positionL3);
        SDL_BlitSurface(l4, NULL, screen, &positionL4);
		SDL_BlitSurface(l5, NULL, screen, &positionL5);
        SDL_BlitSurface(l6, NULL, screen, &positionL6);
        SDL_BlitSurface(l7, NULL, screen, &positionL7);
        SDL_BlitSurface(l8, NULL, screen, &positionL8);
        SDL_Flip(screen);
    }

	/* FREE MEMORY */

	TTF_CloseFont(font);
	TTF_CloseFont(num);
	TTF_CloseFont(infos);
    TTF_Quit();

    SDL_FreeSurface(background);
    SDL_FreeSurface(levelInfos);
    SDL_FreeSurface(time);
    SDL_FreeSurface(score);
    SDL_FreeSurface(hostages);
    SDL_FreeSurface(l1);
    SDL_FreeSurface(l2);
    SDL_FreeSurface(l3);
    SDL_FreeSurface(l4);
    SDL_FreeSurface(l5);
    SDL_FreeSurface(l6);
    SDL_FreeSurface(l7);
    SDL_FreeSurface(l8);

	FMOD_Sound_Release(dialSound);
	return 0;
}

