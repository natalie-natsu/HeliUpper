#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "..\Headers\enums.h"

int enemy_randomness(Level* level, int* tempsPrecedent8, int* tempsActuel8);
int tank_apparition(Player* player, int* limitApparationTank);
void tank_generation(Player* player, Tank* tanks, int* nbTanks);
void tank_moving(Tank* tanks, Player* player, int* nbTanks, int* tempsPrecedent6, int* tempsActuel6);
int saucer_apparition(Player* player, int* limitApparationSaucer, int* nbMissiles);
void saucer_generation(Player* player, Saucer* saucers, int* nbSaucers);
void saucer_moving(Saucer* saucers, Player* player, int* nbSaucers, int* tempsPrecedent9, int* tempsActuel9);
int plane_apparition(Player* player, int* limitApparationPlane);
void plane_generation(Player* player, Plane* planes, int* nbPlanes);
void plane_moving(Plane* planes, Player* player, int* nbPlanes, int* tempsPrecedent11, int* tempsActuel11);
void missilesPlanes(PlaneMissiles* planesMissiles, Player* player, int* nbPlanesMissiles, int* nbPlanes,  Plane* planes, int* tempsPrecedent13, int* tempsActuel13);
void hostages_generation(int* buildingPosX, Hostages* hostages, int* nbHostages);
void hostages_moving(Hostages* hostages, Player* player, int* nbHostages, int* tempsPrecedent14, int* tempsActuel14);

#endif // ENNEMY_H_INCLUDED
