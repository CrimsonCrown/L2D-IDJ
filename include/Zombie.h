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

class Zombie : public Component{
public:
	Zombie(GameObject& associated);
	void Damage(int damage);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	Sound deathSound;
	Sound hitSound;
	int hitpoints;
};

#endif