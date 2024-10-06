#include "Zombie.h"
#include "SpriteRenderer.h"
#include "AnimationSetter.h"
#include "InputManager.h"

Zombie::Zombie(GameObject& associated) : Component(associated){
	hitpoints=100;
	SpriteRenderer* newspr = new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2);
	associated.AddComponent(newspr);
	//newspr->SetAnimation(Animation(0,3,10));
	AnimationSetter* anims = new AnimationSetter(associated);
	associated.AddComponent(anims);
	anims->AddAnimation("walking", Animation(0, 3, 10));
	anims->AddAnimation("dead", Animation(5, 5, 0));
	anims->SetAnimation("walking");
	deathSound = Sound("Recursos/audio/Dead.wav");
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
		deathSound.Play(1);
	}
	else {
		//((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("dead");
		hitSound.Play(1);
	}
	return;
}

void Zombie::Update(float dt){
	if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
		if (associated.box.Contains({ (float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()})) {
			Damage(30);
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