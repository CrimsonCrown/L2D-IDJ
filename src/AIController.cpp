#include "AIController.h"
#include "Character.h"

int AIController::npcCount = 0;

AIController::AIController(GameObject& associated) : Component(associated) {
	npcCount++;
	return;
}

AIController::~AIController(){
	npcCount--;
	return;
}


void AIController::Start() {
	return;
}

void AIController::Update(float dt) {
	/*float x = 0;
	float y = 0;
	if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
		y--;
	}
	if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
		y++;
	}
	if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
		x--;
	}
	if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
		x++;
	}
	if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
		float x = (float)InputManager::GetInstance().GetMouseX() + Camera::pos.x;
		float y = (float)InputManager::GetInstance().GetMouseY() + Camera::pos.y;
		((Character*)associated.GetComponent("Character"))->Issue(Character::Command(Character::Command::SHOOT, x, y));
	}
	if (x != 0 || y != 0) {
		((Character*)associated.GetComponent("Character"))->Issue(Character::Command(Character::Command::MOVE, x, y));
	}*/
	if (Character::player == nullptr) {
		return;
	}
	if (state == RESTING) {
		if (restTimer.Get() > 2) {
			destination = Character::player->Position();
			state = MOVING;
		}
		else {
			restTimer.Update(dt);
		}
	}
	else {
		if (associated.box.Center().DistTo(Character::player->Position()) < 300) {
			state = RESTING;
			restTimer.Restart();
			destination = Character::player->Position();
			associated.GetComponent<Character>()->Issue(Character::Command(Character::Command::SHOOT, destination.x, destination.y));
		}
		else {
			Vec2 boxPos = Character::player->Position().Sub(associated.box.Center());
			associated.GetComponent<Character>()->Issue(Character::Command(Character::Command::MOVE, boxPos.x, boxPos.y));
		}
	}
	return;
}

void AIController::Render() {
	return;
}
