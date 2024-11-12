#ifndef ANIMATOR_INCLUDE
#define ANIMATOR_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "Component.h"
#include "GameObject.h"
#include "Animation.h"

class Animator : public Component{
public:
	Animator(GameObject& associated);
	void Update(float dt);
	void Render();
	void AddAnimation(std::string name, Animation anim);
	void SetAnimation(std::string name);
private:
	std::string current;
	std::unordered_map<std::string, Animation> animations;
	int frameStart;
	int frameEnd;
	float frameTime;
	int currentFrame;
	float timeElapsed;
};

#endif