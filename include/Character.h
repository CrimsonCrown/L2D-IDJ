#ifndef CHARACTER_INCLUDE
#define CHARACTER_INCLUDE

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

class Character : public Component{
public:
	Character(GameObject& associated, std::string sprite);
	~Character();
	void Start();
	void Update(float dt);
	void Render();
	class Command {
	public:
		enum CommandType { MOVE, SHOOT };
		Command(CommandType type, float x, float y) {
			this->type = type;
			pos.x = x;
			pos.y = y;
		};
		CommandType type;
		Vec2 pos;
	private:
	};
	void Issue(Command task);
	static Character* player;
private:
	std::queue<Command> taskQueue;
	std::weak_ptr<GameObject> gun;
	Vec2 speed;
	float linearSpeed;
	int hp;
	Timer deathTimer;
};

#endif