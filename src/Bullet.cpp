#include "Bullet.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Character.h"
#include "Zombie.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool tp) : Component(associated){
	targetsPlayer = tp;
	SpriteRenderer* newspr=new SpriteRenderer((associated),"Recursos/img/Bullet.png");
	associated.AddComponent(newspr);
	this->speed.x=speed;
	this->speed=this->speed.Rotate(angle);
	this->damage=damage;
	distanceLeft=maxDistance;
	return;
}

void Bullet::Update(float dt){
	Vec2 distToMove=speed.Mul(dt);
	associated.box=associated.box.Add(distToMove);
	float distmoved=distToMove.Magnitude();
	distanceLeft-=distmoved;
	if(distanceLeft<=0){
		associated.RequestDelete();
	}
	return;
}

void Bullet::Start() {
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
}

void Bullet::Render(){
	return;
}

int Bullet::GetDamage(){
	return damage;
}

void Bullet::NotifyCollision(GameObject& other) {
	if (other.GetComponent<Zombie>() != nullptr) {
		associated.RequestDelete();
	}
	if (other.GetComponent<Character>() != nullptr) {
		if (targetsPlayer) {
			if (other.GetComponent<Character>() == Character::player) {
				associated.RequestDelete();
			}
		}
		else {
			if (other.GetComponent<Character>() != Character::player) {
				associated.RequestDelete();
			}
		}
	}
	return;
}