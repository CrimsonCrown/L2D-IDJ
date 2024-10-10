#ifndef STATE_INCLUDE
#define STATE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

class State{
public:
	State();
	~State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	std::weak_ptr<GameObject> AddObject(GameObject* go);
	std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
private:
	std::vector<std::shared_ptr<GameObject>> objectArray;
	Music music;
	bool quitRequested;
	bool started;
};

#endif