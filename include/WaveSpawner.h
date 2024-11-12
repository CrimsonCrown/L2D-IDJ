#ifndef WAVESPAWNER_INCLUDE
#define WAVESPAWNER_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <vector>

#include "Component.h"
#include "Timer.h"
#include "Wave.h"


class WaveSpawner : public Component {
public:
	WaveSpawner(GameObject& associated);
	void Start();
	void Update(float dt);
	void Render();
private:
	int zombieCounter;
	Timer zombieCooldownTimer;
	int npcCounter;
	Timer npcCooldownTimer;
	std::vector<Wave> waves;
	int currentWave;
};

#endif