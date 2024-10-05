#include "Zombie.h"
#include "SpriteRenderer.h"
#include "AnimationSetter.h"

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
	return;
}

void Zombie::Damage(int damage){
	hitpoints-=damage;
	if(hitpoints<=0){
		((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("dead");
	}
	return;
}

void Zombie::Update(float dt){
	Damage(1);
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