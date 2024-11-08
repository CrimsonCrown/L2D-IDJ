#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <bits/stdc++.h> 
#include "StageState.h"
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
#include "GameData.h"
#include "Game.h"
#include "EndState.h"

#define PI 3.1415926

StageState::StageState(){
	quitRequested=false;
	started = false;
	music.Open("Recursos/audio/BGM.wav");
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

StageState::~StageState() {
	objectArray.clear();
}

void StageState::LoadAssets(){
	return;
}

void StageState::Update(float dt){
	//TODO: clisoes, entidades
	//checa quit
	if(InputManager::GetInstance().IsKeyDown(ESCAPE_KEY)){
		popRequested = true;
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
	UpdateArray(dt);
	for (index = 0; index < objectArray.size(); index++) {
		if (objectArray[index]->GetComponent<Collider>() != nullptr) {
			for (indexaux = index; indexaux < objectArray.size(); indexaux++) {
				if (indexaux != index) {
					if (objectArray[indexaux]->GetComponent<Collider>() != nullptr) {
						if (Collision::IsColliding(objectArray[index]->GetComponent<Collider>()->box,
							objectArray[indexaux]->GetComponent<Collider>()->box,
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
	if (Character::player == nullptr) {
		GameData::playerVictory = false;
		popRequested = true;
		Game& game = Game::GetInstance();
		game.Push(new EndState());
	}
	else if (WaveSpawner::wavespawnCounter == 0) {
		GameData::playerVictory = true;
		popRequested = true;
		Game& game = Game::GetInstance();
		game.Push(new EndState());
	}
	return;
}

bool ZYSort(std::shared_ptr<GameObject> o1, std::shared_ptr<GameObject> o2){
	if (o1->z == o2->z) {
		return ((o1->box.y+o1->box.h) < (o2->box.y + o2->box.h));
	}
	return (o1->z < o2->z);
}

void StageState::Render(){
	sort(objectArray.begin(), objectArray.end(), ZYSort);
	RenderArray();
	return;
}

void StageState::Start() {
	LoadAssets();
	StartArray();
	started = true;
	return;
}

void StageState::Pause() {
	return;
}

void StageState::Resume() {
	return;
}
