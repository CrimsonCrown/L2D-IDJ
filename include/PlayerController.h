#ifndef PLAYERCONTROLLER_INCLUDE
#define PLAYERCONTROLLER_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"


class PlayerController : public Component {
public:
	PlayerController(GameObject& associated);
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif