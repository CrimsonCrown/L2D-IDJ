#include "WaveSpawner.h"
#include "Character.h"
#include "Zombie.h"
#include "AIController.h"
#include "Game.h"

#define PI 3.1415926

WaveSpawner::WaveSpawner(GameObject& associated) : Component(associated) {
	zombieCounter = 0;
	npcCounter = 0;
	currentWave = 0;
	waves.push_back(Wave(5,3,0,0));
	waves.push_back(Wave(10, 2,0,0));
	waves.push_back(Wave(15, 1.5,2,15));
	return;
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
	zombieCooldownTimer.Update(dt);
	npcCooldownTimer.Update(dt);
	if (zombieCounter < waves[currentWave].zombies) {
		if (zombieCooldownTimer.Get() >= waves[currentWave].cooldown) {
			Vec2 offset = GetOffset();
			//std::cout << "spawnoffset: " << offset.x << " " << offset.y << "\n";
			//zombie
			GameObject* zombs = new GameObject();
			Zombie* newzomb = new Zombie((*zombs));
			zombs->AddComponent(newzomb);
			zombs->box.x = offset.x + Camera::pos.x+600;
			zombs->box.y = offset.y + Camera::pos.y+450;
			Game::GetInstance().GetState().AddObject(zombs);
			zombieCooldownTimer.Restart();
			zombieCounter++;
		}
	}
	if (npcCounter < waves[currentWave].npcs) {
		if (npcCooldownTimer.Get() >= waves[currentWave].npccooldown) {
			Vec2 offset = GetOffset();
			//std::cout << "spawnoffset: " << offset.x << " " << offset.y << "\n";
			//Character
			GameObject* npc = new GameObject();
			AIController* newctrl = new AIController((*npc));
			npc->AddComponent(newctrl);
			Character* newch = new Character((*npc), "Recursos/img/NPC.png");
			npc->AddComponent(newch);
			npc->box.x = offset.x + Camera::pos.x + 600;
			npc->box.y = offset.y + Camera::pos.y + 450;
			Game::GetInstance().GetState().AddObject(npc);
			npcCooldownTimer.Restart();
			npcCounter++;
		}
	}
	if(zombieCounter >= waves[currentWave].zombies && npcCounter >= waves[currentWave].npcs && Zombie::zombieCounter<=0 && AIController::npcCount<=0) {
		currentWave++;
		zombieCounter = 0;
		npcCounter = 0;
		if ((unsigned int)currentWave >= waves.size()) {
			associated.RequestDelete();
		}
	}
	return;
}

void WaveSpawner::Render() {
	return;
}
