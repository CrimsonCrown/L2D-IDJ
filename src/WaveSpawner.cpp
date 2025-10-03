#include "WaveSpawner.h"
#include "Character.h"
#include "Zombie.h"
#include "AIController.h"
#include "Game.h"

#define PI 3.1415926

int WaveSpawner::wavespawnCounter = 0;

WaveSpawner::WaveSpawner(GameObject& associated) : Component(associated) {
	currentWave = 0;
	waves.push_back(Wave());
	waves[0].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[0].Issue(Wave::Command(Wave::Command::WAIT, 3));
	waves[0].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[0].Issue(Wave::Command(Wave::Command::WAIT, 3));
	waves[0].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[0].Issue(Wave::Command(Wave::Command::WAIT, 3));
	waves[0].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[0].Issue(Wave::Command(Wave::Command::WAIT, 3));
	waves[0].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves.push_back(Wave());
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[1].Issue(Wave::Command(Wave::Command::WAIT, 2));
	waves[1].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves.push_back(Wave());
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 3));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNNPC, 1));
	waves[2].Issue(Wave::Command(Wave::Command::WAIT, 3));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[2].Issue(Wave::Command(Wave::Command::WAIT, 1.5));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[2].Issue(Wave::Command(Wave::Command::WAIT, 1.5));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[2].Issue(Wave::Command(Wave::Command::WAIT, 1.5));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[2].Issue(Wave::Command(Wave::Command::WAIT, 1.5));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[2].Issue(Wave::Command(Wave::Command::WAIT, 1.5));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[2].Issue(Wave::Command(Wave::Command::WAIT, 1.5));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 1));
	waves[2].Issue(Wave::Command(Wave::Command::WAIT, 1.5));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNZ, 5));
	waves[2].Issue(Wave::Command(Wave::Command::SPAWNNPC, 1));
	wavespawnCounter++;
	waiting=false;
	waitThreshold=0;
	return;
}

WaveSpawner::~WaveSpawner() {
	wavespawnCounter--;
}

void WaveSpawner::Start() {
	return;
}

Vec2 GetOffset() {
	float angle = std::rand() % 360;
	Vec2 offset(1500, 0);
	offset = offset.Rotate((angle / 360) * 2 * PI);
	float offsetxmult = 600.0 / std::abs(offset.x);
	float offsetymult = 450.0 / std::abs(offset.y);
	offset = offset.Mul(std::min(offsetxmult, offsetymult));
	//std::cout << "spawnoffset: " << offset.x << " " << offset.y << "\n";
	if (offset.x <= -600) {
		offset.x -= 74;
	}
	if (offset.y <= -450) {
		offset.y -= 74;
	}
	return offset;
}

void WaveSpawner::Update(float dt) {
	waitTimer.Update(dt);
	if(waiting){
		if(waitTimer.Get()>waitThreshold){
			waiting=false;
		}
	}
	while (waves[currentWave].taskQueue.size() > 0 && !waiting) {
		Wave::Command todo = waves[currentWave].taskQueue.front();
		if (todo.type == Wave::Command::SPAWNZ) {
			for(int i=(int)todo.quantity;i>0;i--){
				Vec2 offset = GetOffset();
				GameObject* zombs = new GameObject();
				Zombie* newzomb = new Zombie((*zombs));
				zombs->AddComponent(newzomb);
				zombs->box.x = offset.x + Camera::pos.x+600;
				zombs->box.y = offset.y + Camera::pos.y+450;
				Game::GetInstance().GetCurrentState().AddObject(zombs);
			}
		}
		else if (todo.type == Wave::Command::SPAWNNPC) {
			for(int i=(int)todo.quantity;i>0;i--){
				Vec2 offset = GetOffset();
				GameObject* npc = new GameObject();
				AIController* newctrl = new AIController((*npc));
				npc->AddComponent(newctrl);
				Character* newch = new Character((*npc), "Recursos/img/NPC.png");
				npc->AddComponent(newch);
				npc->box.x = offset.x + Camera::pos.x + 600;
				npc->box.y = offset.y + Camera::pos.y + 450;
				Game::GetInstance().GetCurrentState().AddObject(npc);
			}
		}
		else if (todo.type == Wave::Command::WAIT){
			waitThreshold=todo.quantity;
			waiting=true;
			waitTimer.Restart();
		}
		waves[currentWave].taskQueue.pop();
	}
	if(Zombie::zombieCounter<=0 && AIController::npcCount<=0 && waves[currentWave].taskQueue.size()<=0) {
		currentWave++;
		if ((unsigned int)currentWave >= waves.size()) {
			associated.RequestDelete();
		}
	}
	return;
}

void WaveSpawner::Render() {
	return;
}
