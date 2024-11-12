#include "Zombie.h"
#include "SpriteRenderer.h"
#include "AnimationSetter.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"
#include "Bullet.h"
#include "Character.h"

int Zombie::zombieCounter = 0;

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
	anims->AddAnimation("walkingLeft", Animation(0, 3, 0.5, SDL_FLIP_HORIZONTAL));
	anims->AddAnimation("dead", Animation(5, 5, 0));
	anims->AddAnimation("hit", Animation(4, 4, 0));
	anims->AddAnimation("hitLeft", Animation(4, 4, 0, SDL_FLIP_HORIZONTAL));
	anims->SetAnimation("walking");
	hitSound = Sound("Recursos/audio/Hit0.wav");
	zombieCounter++;
	movingleft = false;
	return;
}

void Zombie::Start() {
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
}

void Zombie::Damage(int damage){
	if(hitpoints<=0){
		return;
	}
	hitpoints-=damage;
	if(hitpoints<=0){
		associated.GetComponent<AnimationSetter>()->SetAnimation("dead");
		deathTimer.Restart();
		deathSound.Play(1);
	}
	else {
		if (movingleft) {
			associated.GetComponent<AnimationSetter>()->SetAnimation("hitLeft");
		}
		else {
			associated.GetComponent<AnimationSetter>()->SetAnimation("hit");
		}
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
			if (movingleft) {
				associated.GetComponent<AnimationSetter>()->SetAnimation("walkingLeft");
			}
			else {
				associated.GetComponent<AnimationSetter>()->SetAnimation("walking");
			}
			hitting = false;
		}
		if (hitting == false) {
			if (Character::player != nullptr) {
				//std::cout << "walkin!\n";
				Vec2 target = Character::player->Position();
				Vec2 diff = target.Sub(associated.box.Center()).Normal().Mul(125*dt);
				//std::cout << "movement: " << diff.x << " " << diff.y << "\n";
				associated.box=associated.box.Add(diff);
				bool isLeft = diff.x < 0;
				bool changedDirection = movingleft != isLeft;
				//std::cout << isLeft << movingleft << changedDirection << "\n";
				if (changedDirection) {
					movingleft = isLeft;
					if (movingleft) {
						associated.GetComponent<AnimationSetter>()->SetAnimation("walkingLeft");
						//std::cout << "going left yay!!!\n";
					}
					else {
						associated.GetComponent<AnimationSetter>()->SetAnimation("walking");
						//std::cout << "going right? nay!!!\n";
					}
				}
			}
		}
		/*if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
			if (associated.box.Contains({ (float)InputManager::GetInstance().GetMouseX() + Camera::pos.x, (float)InputManager::GetInstance().GetMouseY() + Camera::pos.y })) {
				Damage(30);
			}
		}*/
	}
	else {
		if (deathTimer.Get() > 5) {
			associated.RequestDelete();
			zombieCounter--;
		}
		else {
			//std::cout << "removes collider hopefully\n";
			associated.RemoveComponent(associated.GetComponent<Collider>());
			//std::cout << "removed collider hopefully\n";
		}
	}
	return;
}

void Zombie::Render(){
	return;
}

void Zombie::NotifyCollision(GameObject& other) {
	if (other.GetComponent<Bullet>() != nullptr) {
		Damage(other.GetComponent<Bullet>()->GetDamage());
	}
	return;
}
