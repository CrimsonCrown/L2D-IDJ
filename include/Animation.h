#ifndef ANIMATION_INCLUDE
#define ANIMATION_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <cmath>

class Animation{
public:
	Animation(int frameStart, int frameEnd, float frameTime);
	int frameStart;
	int frameEnd;
	float frameTime;
private:
};

#endif