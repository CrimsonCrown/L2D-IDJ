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
	~WaveSpawner();
	void Start();
	void Update(float dt);
	void Render();
	static int wavespawnCounter;
private:
	Timer waitTimer;
	bool waiting;
	float waitThreshold;
	std::vector<Wave> waves;
	int currentWave;
};

#endif