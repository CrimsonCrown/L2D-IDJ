#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileMap.h"
#include "InputManager.h"

State::State(){
	quitRequested=false;
	LoadAssets();
	music.Play();
	//background
	GameObject* bg = new GameObject();
	SpriteRenderer* newspr = new SpriteRenderer((*bg), "Recursos/img/Background.png", 1, 1);
	bg->AddComponent(newspr);
	AddObject(bg);
	//map
	GameObject* map = new GameObject();
	TileMap* mapping = new TileMap((*map), "Recursos/map/map.txt", new TileSet(64, 64, "Recursos/img/Tileset.png"));
	map->AddComponent(mapping);
	AddObject(map);
	return;
}

State::~State() {
	objectArray.clear();
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::LoadAssets(){
	music.Open("Recursos/audio/stageState.ogg");
	return;
}

void State::Update(float dt){
	//TODO: clisoes, entidades
	//checa quit
	if(InputManager::GetInstance().IsKeyDown(ESCAPE_KEY)){
		quitRequested = true;
	}
	if (InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}
	if (InputManager::GetInstance().KeyPress(' ')) {
		//zombie
		GameObject* zombs = new GameObject();
		Zombie* newzomb = new Zombie((*zombs));
		zombs->AddComponent(newzomb);
		zombs->box.x = InputManager::GetInstance().GetMouseX();
		zombs->box.y = InputManager::GetInstance().GetMouseY();
		AddObject(zombs);
	}
	long unsigned int index;
	for (index = 0; index < objectArray.size(); index++) {
		objectArray[index]->Update(dt);
	}
	for (index = 0; index < objectArray.size(); index++) {
		if (objectArray[index]->IsDead()) {
			objectArray.erase(objectArray.begin() + index);
		}
	}
	return;
}

void State::Render(){
	long unsigned int index;
	for (index = 0; index < objectArray.size(); index++) {
		objectArray[index]->Render();
	}
	return;
}

void State::AddObject(GameObject* go) {
	objectArray.emplace_back(go);
}