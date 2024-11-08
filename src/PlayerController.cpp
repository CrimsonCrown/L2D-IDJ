#include "PlayerController.h"
#include "Character.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {
	return;
}

void PlayerController::Start() {
	return;
}

void PlayerController::Update(float dt) {
	float x = 0;
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
		associated.GetComponent<Character>()->Issue(Character::Command(Character::Command::SHOOT, x, y));
	}
	if (x != 0 || y != 0) {
		associated.GetComponent<Character>()->Issue(Character::Command(Character::Command::MOVE, x, y));
	}
	return;
}

void PlayerController::Render() {
	return;
}
