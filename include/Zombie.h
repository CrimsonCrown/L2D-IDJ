#ifndef ZOMBIE_INCLUDE
#define ZOMBIE_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component{
public:
	Zombie(GameObject& associated);
	void Damage(int damage);
	void Update(float dt);
	void Render();
private:
	Sound deathSound;
	Sound hitSound;
	int hitpoints;
	Timer hitTimer;
	bool hitting;
	Timer deathTimer;
};

#endif