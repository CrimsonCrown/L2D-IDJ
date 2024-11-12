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
	deathSound = Sound("Recursos/audio/Dead.wav");
	return;
}

void Zombie::Damage(int damage){
	if(hitpoints<=0){
		return;
	}
	hitpoints-=damage;
	if(hitpoints<=0){
		associated.GetComponent<AnimationSetter>()->SetAnimation("dead");
		deathSound.Play(1);
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
