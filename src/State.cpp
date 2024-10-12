#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <bits/stdc++.h> 
#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "Character.h"
#include "PlayerController.h"
#include "Collision.h"
#include "Collider.h"
#include "WaveSpawner.h"

#define PI 3.1415926

State::State(){
	quitRequested=false;
	music.Open("Recursos/audio/stageState.ogg");
	music.Play();
	//background
	GameObject* bg = new GameObject();
	SpriteRenderer* newspr = new SpriteRenderer((*bg), "Recursos/img/Background.png", 1, 1);
	newspr->SetCameraFollower(true);
	bg->AddComponent(newspr);
	bg->z = -2;
	AddObject(bg);
	//map
	GameObject* map = new GameObject();
	TileMap* mapping = new TileMap((*map), "Recursos/map/map.txt", new TileSet(64, 64, "Recursos/img/Tileset.png"));
	map->AddComponent(mapping);
	map->z = -1;
	AddObject(map);
	//player character
	GameObject* pc = new GameObject();
	PlayerController* newpctrl = new PlayerController((*pc));
	pc->AddComponent(newpctrl);
	Character* newch = new Character((*pc), "Recursos/img/Player.png");
	Character::player = newch;
	pc->AddComponent(newch);
	pc->box.x = 1280;
	pc->box.y = 1280;
	Camera::Follow(pc);
	AddObject(pc);
	//wave spawner
	GameObject* ws = new GameObject();
	WaveSpawner* newws = new WaveSpawner((*ws));
	ws->AddComponent(newws);
	AddObject(ws);
	return;
}

State::~State() {
	objectArray.clear();
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::LoadAssets(){
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
	/*if (InputManager::GetInstance().KeyPress(' ')) {
		//zombie
		GameObject* zombs = new GameObject();
		Zombie* newzomb = new Zombie((*zombs));
		zombs->AddComponent(newzomb);
		zombs->box.x = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
		zombs->box.y = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
		AddObject(zombs);
	}*/
	Camera::Update(dt);
	long unsigned int index;
	long unsigned int indexaux;
	for (index = 0; index < objectArray.size(); index++) {
		objectArray[index]->Update(dt);
	}
	for (index = 0; index < objectArray.size(); index++) {
		if (objectArray[index]->GetComponent("Collider") != nullptr) {
			for (indexaux = index; indexaux < objectArray.size(); indexaux++) {
				if (indexaux != index) {
					if (objectArray[indexaux]->GetComponent("Collider") != nullptr) {
						if (Collision::IsColliding(((Collider*)objectArray[index]->GetComponent("Collider"))->box,
							((Collider*)objectArray[indexaux]->GetComponent("Collider"))->box,
							(objectArray[index]->angleDeg / 360) * 2 * PI,
							(objectArray[indexaux]->angleDeg / 360) * 2 * PI)) {
							objectArray[index]->NotifyCollision(*objectArray[indexaux]);
							objectArray[indexaux]->NotifyCollision(*objectArray[index]);

						}
					}
				}
			}
		}
	}
	for (index = 0; index < objectArray.size(); index++) {
		if (objectArray[index]->IsDead()) {
			objectArray.erase(objectArray.begin() + index);
		}
	}
	return;
}

bool ZYSort(std::shared_ptr<GameObject> o1, std::shared_ptr<GameObject> o2){
	if (o1->z == o2->z) {
		return ((o1->box.y+o1->box.h) < (o2->box.y + o2->box.h));
	}
	return (o1->z < o2->z);
}

void State::Render(){
	long unsigned int index;
	sort(objectArray.begin(), objectArray.end(), ZYSort);
	for (index = 0; index < objectArray.size(); index++) {
		objectArray[index]->Render();
	}
	return;
}

void State::Start() {
	LoadAssets();
	long unsigned int index;
	for (index = 0; index < objectArray.size(); index++) {
		objectArray[index]->Start();
	}
	started = true;
	return;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	//constroi shared ptr
	std::shared_ptr<GameObject> newobj(go);
	//coloca no vetor
	objectArray.push_back(newobj);
	//start caso necessario
	if (started) {
		newobj->Start();
	}
	//retorna weak ptr
	std::weak_ptr<GameObject> newweak(newobj);
	return newweak;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	//varre vetor
	long unsigned int index;
	for (index = 0; index < objectArray.size(); index++) {
		if (objectArray[index].get() == go) {
			std::weak_ptr<GameObject> newweak(objectArray[index]);
			return newweak;
		}
	}
	std::weak_ptr<GameObject> newweak;
	return newweak;
}