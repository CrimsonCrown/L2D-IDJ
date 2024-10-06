#ifndef SOUND_INCLUDE
#define SOUND_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Resources.h"

class Sound{
public:
	Sound();
	Sound(std::string file);
	~Sound();
	void Play(int times=1);
	void Stop();
	void Open(std::string file);
	bool IsOpen();
private:
	Mix_Chunk* chunk;
	int channel;
};

#endif