#ifndef ANIMATION_INCLUDE
#define ANIMATION_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <cmath>

class Animation{
public:
	Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int frameStart;
	int frameEnd;
	float frameTime;
	SDL_RendererFlip flip;
private:
};

#endif