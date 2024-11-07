#include "Character.h"
#include "Game.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "AnimationSetter.h"

#define PI 3.1415926

Character* Character::player;

Character::Character(GameObject& associated, std::string sprite) : Component(associated){
	//Collider* newcol=new Collider((associated));
	//associated.AddComponent(newcol);
	//cria sprite
	SpriteRenderer* newspr = new SpriteRenderer(associated, sprite, 3, 4);
	associated.AddComponent(newspr);
	//newspr->SetAnimation(Animation(0,3,10));
	AnimationSetter* anims = new AnimationSetter(associated);
	associated.AddComponent(anims);
	anims->AddAnimation("walkingRight", Animation(0, 5, 0.3));
	anims->AddAnimation("walkingLeft", Animation(0, 5, 0.3, SDL_FLIP_HORIZONTAL));
	anims->AddAnimation("idle", Animation(6, 9, 0.5));
	anims->AddAnimation("dead", Animation(10, 11, 0.5));
	anims->SetAnimation("idle");
	//outros atributos
	linearSpeed=50;
	hp=100;
	return;
}

Character::~Character(){
	if (this == player) {
		player = nullptr;
	}
	return;
}

void Character::Start(){
	//cria PenguinCannon
	GameObject* gunBuddy=new GameObject();
	Gun* newgun=new Gun((*gunBuddy),Game::GetInstance().GetState().GetObjectPtr(&associated));
	gunBuddy->AddComponent(newgun);
	gun=Game::GetInstance().GetState().AddObject(gunBuddy);
	return;
}

void Character::Update(float dt){
	bool moved = false;
	bool left = false;
	while (taskQueue.size() > 0) {
		Command todo = taskQueue.front();
		if (todo.type == Command::MOVE) {
			speed = todo.pos.Normal().Mul(linearSpeed * dt);
			associated.box = associated.box.Add(speed);
			moved = true;
			if (todo.pos.x < 0) {
				left = true;
			}
		}
		else if (todo.type == Command::SHOOT) {
			gun.lock()->GetComponent<Gun>()->Shoot(todo.pos);
		}
		taskQueue.pop();
	}
	if (moved) {
		if (left) {
			associated.GetComponent<AnimationSetter>()->SetAnimation("walkingLeft");
		}
		else {
			associated.GetComponent<AnimationSetter>()->SetAnimation("walkingRight");
		}
	}
	else {
		associated.GetComponent<AnimationSetter>()->SetAnimation("idle");
	}
	if (hp <= 0 && deathTimer.Get()>3) {
		associated.RequestDelete();
	}
	return;
}

void Character::Render(){
	return;
}

void Character::Issue(Command task) {
	taskQueue.push(task);
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

/*Vec2 PenguinBody::Position(){
	return associated.box.Center();
}*/