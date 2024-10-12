#ifndef WAVE_INCLUDE
#define WAVE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <cmath>

class Wave{
public:
	Wave(int zombies, float cooldown, int npcs, float npccooldown);
	int zombies;
	float cooldown;
	int npcs;
	float npccooldown;
private:
};

#endif