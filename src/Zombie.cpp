#include "Zombie.h"
#include "SpriteRenderer.h"
#include "AnimationSetter.h"
#include "InputManager.h"
#include "Camera.h"

Zombie::Zombie(GameObject& associated) : Component(associated){
	hitting = false;
	deathSound = Sound("Recursos/audio/Dead.wav");
	hitpoints=100;
	SpriteRenderer* newspr = new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2);
	associated.AddComponent(newspr);
	//newspr->SetAnimation(Animation(0,3,10));
	AnimationSetter* anims = new AnimationSetter(associated);
	associated.AddComponent(anims);
	anims->AddAnimation("walking", Animation(0, 3, 0.5));
	anims->AddAnimation("dead", Animation(5, 5, 0));
	anims->AddAnimation("hit", Animation(4, 4, 0));
	anims->SetAnimation("walking");
	hitSound = Sound("Recursos/audio/Hit0.wav");
	return;
}

void Zombie::Damage(int damage){
	if(hitpoints<=0){
		return;
	}
	hitpoints-=damage;
	if(hitpoints<=0){
		((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("dead");
		deathTimer.Restart();
		deathSound.Play(1);
	}
	else {
		((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("hit");
		hitTimer.Restart();
		hitting = true;
		hitSound.Play(1);
	}
	return;
}

void Zombie::Update(float dt){
	hitTimer.Update(dt);
	deathTimer.Update(dt);
	if (hitpoints > 0) {
		if (hitting == true && hitTimer.Get() > 0.5) {
			((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("walking");
			hitting = false;
		}
		if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
			if (associated.box.Contains({ (float)InputManager::GetInstance().GetMouseX() + Camera::pos.x, (float)InputManager::GetInstance().GetMouseY() + Camera::pos.y })) {
				Damage(30);
			}
		}
	}
	else {
		if (deathTimer.Get() > 5) {
			associated.RequestDelete();
		}
	}
	return;
}

void Zombie::Render(){
	return;
}

bool Zombie::Is(std::string type){
	if(type=="Zombie"){
		return true;
	}
	return false;
}