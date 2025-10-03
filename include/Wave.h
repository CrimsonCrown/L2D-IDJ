#ifndef WAVE_INCLUDE
#define WAVE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <cmath>
#include <queue>

class Wave{
public:
	Wave();
	class Command {
	public:
		enum CommandType {SPAWNZ,SPAWNNPC,WAIT};
		Command(CommandType type, float quantity) {
			this->type = type;
			this->quantity = quantity;
		};
		CommandType type;
		float quantity;
	private:
	};
	void Issue(Command task);
	std::queue<Command> taskQueue;
private:
};

#endif