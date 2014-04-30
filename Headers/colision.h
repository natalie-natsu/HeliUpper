#ifndef COLISION_H_INCLUDED
#define COLISION_H_INCLUDED

void collision(Hostages* hostages, int* nbHostages, Building* buildings, Missiles* missiles, PlaneMissiles* planesMissiles, Tank* tanks, Plane* planes, Saucer* saucers, Player* player, int* nbTanks, int* nbPlanes, int* nbSaucers, int* nbMissiles, int* nbPlanesMissiles, int* tempsPrecedent7, int* tempsActuel7, int* tempsPrecedent10, int* tempsActuel10, int* tempsPrecedent12, int* tempsActuel12, FMOD_SYSTEM* system);
int collisionBuilding(int* nbMissiles, Building* buildings, Missiles* missiles);

#endif // COLISION_H_INCLUDED
