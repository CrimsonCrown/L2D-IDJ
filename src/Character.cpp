#include "Character.h"
#include "Game.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "AnimationSetter.h"
#include "Collider.h"
#include "Bullet.h"

#define PI 3.1415926

Character* Character::player;

Character::Character(GameObject& associated, std::string sprite) : Component(associated){
	deathSound = Sound("Recursos/audio/Dead.wav");
	//cria sprite
	SpriteRenderer* newspr = new SpriteRenderer(associated, sprite, 3, 4);
	associated.AddComponent(newspr);
	//newspr->SetAnimation(Animation(0,3,10));
	AnimationSetter* anims = new AnimationSetter(associated);
	associated.AddComponent(anims);
	anims->AddAnimation("walkingRight", Animation(0, 5, 0.2));
	anims->AddAnimation("walkingLeft", Animation(0, 5, 0.2, SDL_FLIP_HORIZONTAL));
	anims->AddAnimation("idle", Animation(6, 9, 0.5));
	anims->AddAnimation("dead", Animation(10, 11, 0.5));
	anims->SetAnimation("idle");
	//outros atributos
	hitting = false;
	linearSpeed=150;
	hp=100;
	hitSound = Sound("Recursos/audio/Hit1.wav");
	return;
}

Character::~Character(){
	if (this == player) {
		player = nullptr;
		Camera::Unfollow();
	}
	return;
}

void Character::Start(){
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria PenguinCannon
	GameObject* gunBuddy=new GameObject();
	Gun* newgun=new Gun((*gunBuddy),Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
	gunBuddy->AddComponent(newgun);
	gun=Game::GetInstance().GetCurrentState().AddObject(gunBuddy);
	return;
}

void Character::Update(float dt){
	bool moved = false;
	bool left = false;
	if (hp > 0) {
		while (taskQueue.size() > 0) {
			Command todo = taskQueue.front();
			if (todo.type == Command::MOVE) {
				speed = todo.pos.Normal().Mul(linearSpeed * dt);
				associated.box = associated.box.Add(speed);
				moved = true;
				if (associated.box.x < 640) {
					associated.box.x = 640;
				}
				if (associated.box.x > 1920-74) {
					associated.box.x = 1920-74;
				}
				if (associated.box.y < 512) {
					associated.box.y = 512;
				}
				if (associated.box.y > 2048-83) {
					associated.box.y = 2048-83;
				}
				if (todo.pos.x < 0) {
					left = true;
				}
			}
			else if (todo.type == Command::SHOOT) {
				((Gun*)(gun.lock()->GetComponent("Gun")))->Shoot(todo.pos);
			}
			taskQueue.pop();
		}
		if (moved) {
			if (left) {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("walkingLeft");
			}
			else {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("walkingRight");
			}
		}
		else {
			((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("idle");
		}
	}
	deathTimer.Update(dt);
	hitTimer.Update(dt);
	if (hp <= 0 && deathTimer.Get()>3) {
		associated.RequestDelete();
	}
	if (hitting == true && hitTimer.Get() > 0.5) {
		hitting = false;
	}
	return;
}

void Character::Render(){
	return;
}

bool Character::Is(std::string type){
	if(type=="Character"){
		return true;
	}
	return false;
}

void Character::Issue(Command task) {
	taskQueue.push(task);
}

void Character::NotifyCollision(GameObject& other) {
	if (other.GetComponent("Zombie") != nullptr && hitting==false) {
		Damage(10);
	}
	if (other.GetComponent("Bullet") != nullptr) {
		if (((Bullet*)other.GetComponent("Bullet"))->targetsPlayer) {
			if (this == player) {
				Damage(((Bullet*)other.GetComponent("Bullet"))->GetDamage());
			}
		}
		else {
			if (this != player) {
				Damage(((Bullet*)other.GetComponent("Bullet"))->GetDamage());
			}
		}
	}
	return;
}

void Character::Damage(int damage) {
	if (hp <= 0) {
		return;
	}
	hp -= damage;
	if (hp <= 0) {
		((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("dead");
		deathTimer.Restart();
		deathSound.Play(1);
	}
	else {
		hitTimer.Restart();
		hitting = true;
		hitSound.Play(1);
	}
	return;
}

/*void PenguinBody::NotifyCollision(GameObject& other){
	if((other.GetComponent("Bullet")!=nullptr)&&(((Bullet*)other.GetComponent("Bullet"))->targetsPlayer==true)){
		hp-=10;
		if(hp<=0){
			Camera::Unfollow();
			GameObject* explosion=new GameObject();
			Sprite* newspr=new Sprite((*explosion),"Recursos/img/penguindeath.png", 5, 0.4, 2);
			explosion->AddComponent(newspr);
			Sound* newsnd=new Sound((*explosion),"Recursos/audio/boom.wav");
			newsnd->Play();
			explosion->AddComponent(newsnd);
			explosion->box=explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Game::GetInstance().GetCurrentState().AddObject(explosion);
			pcannon.lock()->RequestDelete();
			associated.RequestDelete();
		}
	}
	return;
}*/

Vec2 Character::Position(){
	return associated.box.Center();
}