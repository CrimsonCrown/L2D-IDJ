#ifndef GUN_INCLUDE
#define GUN_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <queue>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Timer.h"

class Gun : public Component{
public:
	Gun(GameObject& associated, std::weak_ptr<GameObject> character);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Shoot(Vec2 target);
private:
	int cooldown;
	Timer cdtimer;
	std::weak_ptr<GameObject> character;
	float angle;
	Sound reloadSound;
	Sound shotSound;
};

#endif