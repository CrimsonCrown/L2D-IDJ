#ifndef AICONTROLLER_INCLUDE
#define AICONTROLLER_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "Timer.h"
#include "Vec2.h"


class AIController : public Component {
public:
	AIController(GameObject& associated);
	~AIController();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	static int npcCount;
private:
	enum AIState { MOVING, RESTING };
	AIState state;
	Timer restTimer;
	Vec2 destination;
};

#endif