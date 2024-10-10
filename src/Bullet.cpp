#include "Bullet.h"
#include "SpriteRenderer.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance) : Component(associated){
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

void Bullet::Render(){
	return;
}

bool Bullet::Is(std::string type){
	if(type=="Bullet"){
		return true;
	}
	return false;
}

int Bullet::GetDamage(){
	return damage;
}