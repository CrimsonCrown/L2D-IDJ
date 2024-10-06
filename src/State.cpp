#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileMap.h"

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
	//zombie
	GameObject* zombs = new GameObject();
	Zombie* newzomb = new Zombie((*zombs));
	zombs->AddComponent(newzomb);
	zombs->box.x = 600;
	zombs->box.y = 450;
	AddObject(zombs);
	//zombie2
	GameObject* zombs2 = new GameObject();
	Zombie* newzomb2 = new Zombie((*zombs2));
	zombs2->AddComponent(newzomb2);
	zombs2->box.x = 300;
	zombs2->box.y = 450;
	AddObject(zombs2);
	//zombie3
	GameObject* zombs3 = new GameObject();
	Zombie* newzomb3 = new Zombie((*zombs3));
	zombs3->AddComponent(newzomb3);
	zombs3->box.x = 900;
	zombs3->box.y = 450;
	AddObject(zombs3);
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
	long unsigned int index;
	for (index = 0; index < objectArray.size(); index++) {
		objectArray[index]->Update(dt);
	}
	for (index = 0; index < objectArray.size(); index++) {
		if (objectArray[index]->IsDead()) {
			objectArray.erase(objectArray.begin() + index);
		}
	}
	quitRequested=SDL_QuitRequested();
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