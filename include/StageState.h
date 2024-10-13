#ifndef STAGESTATE_INCLUDE
#define STAGESTATE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "State.h"


class StageState : public State {
public:
	StageState();
	~StageState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
private:
	Music music;
};
#endif