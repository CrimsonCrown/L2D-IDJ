#ifndef ANIMATIONSETTER_INCLUDE
#define ANIMATIONSETTER_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "Component.h"
#include "GameObject.h"
#include "Animation.h"

class AnimationSetter : public Component{
public:
	AnimationSetter(GameObject& associated);
	void Update(float dt);
	void Render();
	void AddAnimation(std::string name, Animation anim);
	void SetAnimation(std::string name);
private:
	std::unordered_map<std::string, Animation> animations;
};

#endif