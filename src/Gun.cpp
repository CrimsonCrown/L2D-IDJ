#include "Gun.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "AnimationSetter.h"
#include "Bullet.h"
#include "Character.h"

#define PI 3.1415926

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character) : Component(associated){
	reloadSound = Sound("Recursos/audio/PumpAction.mp3");
	//cria sprite
	SpriteRenderer* newspr = new SpriteRenderer(associated, "Recursos/img/Gun.png", 3, 2);
	associated.AddComponent(newspr);
	//newspr->SetAnimation(Animation(0,3,10));
	AnimationSetter* anims = new AnimationSetter(associated);
	associated.AddComponent(anims);
	anims->AddAnimation("idle", Animation(0, 0, 0));
	anims->AddAnimation("idleFlip", Animation(0, 0, 0, SDL_FLIP_VERTICAL));
	anims->AddAnimation("reloading", Animation(1, 5, 0.1));
	anims->AddAnimation("reloadingFlip", Animation(1, 5, 0.1, SDL_FLIP_VERTICAL));
	anims->SetAnimation("idle");
	//cria collider
	//Collider* newcol=new Collider((associated));
	//associated.AddComponent(newcol);
	//outros atributos
	this->character=character;
	angle=0;
	cooldown=0;
	shotSound = Sound("Recursos/audio/Range.wav");
	return;
}

void Gun::Update(float dt){
	std::shared_ptr<GameObject> ch=character.lock();
	if(ch==nullptr){
		associated.RequestDelete();
		return;
	}
	//move para o centro do corpo
	associated.box=associated.box.Add(ch->box.Center().Sub(associated.box.Center()));
	associated.box = associated.box.Add(Vec2(75,0).Rotate(angle));
	//std::cout << "box.x=" << associated.box.x << " box.y=" << associated.box.y << " center.x=" << associated.box.Center().x << " center.y=" << associated.box.Center().y << " chcenter.x=" << ch->box.Center().x << " chcenter.y=" << ch->box.Center().y << "\n" << " ch.x=" << ch->box.x << " ch.y=" << ch->box.y << "\n" << " ch.w=" << ch->box.w << " ch.h=" << ch->box.h << "\n";
	cdtimer.Update(dt);
	if (cooldown == 1) {
		if (cdtimer.Get() > 0.3) {
			cdtimer.Restart();
			if (associated.angleDeg > 90 || associated.angleDeg < -90) {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("reloadingFlip");
			}
			else {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("reloading");
			}
			reloadSound.Play(1);
			cooldown++;
		}
	}
	else if (cooldown == 2) {
		if (cdtimer.Get() > 0.5) {
			cdtimer.Restart();
			if (associated.angleDeg > 90 || associated.angleDeg < -90) {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("idleFlip");
			}
			else {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("idle");
			}
			cooldown++;
		}
	}
	else if (cooldown == 3) {
		if (cdtimer.Get() > 0.2) {
			cdtimer.Restart();
			cooldown=0;
		}
	}
	return;
}

void Gun::Render(){
	return;
}

bool Gun::Is(std::string type){
	if(type=="Gun"){
		return true;
	}
	return false;
}

void Gun::Shoot(Vec2 target){
	if (cooldown == 0) {
		std::shared_ptr<GameObject> ch = character.lock();
		angle = target.Sub(ch->box.Center()).Incline();
		//move para o centro do corpo
		associated.box = associated.box.Add(ch->box.Center().Sub(associated.box.Center()));
		associated.box = associated.box.Add(Vec2(75, 0).Rotate(angle));
		associated.angleDeg = ((angle * 360) / (2 * PI));
		if (associated.angleDeg > 90 || associated.angleDeg < -90) {
			((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("idleFlip");
		}
		else {
			((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetAnimation("idle");
		}
		//std::cout << " t.x : " << target.x << " t.y : " << target.y << " center.x : " << ch->box.x << " center.y : " << ch->box.x << " incline : " << angle << " \n";
		cooldown = 1;
		cdtimer.Restart();
		shotSound.Play(1);
		//cria bullet
		GameObject* bullet = new GameObject();
		bool tp;
		if (ch->GetComponent("Character") != Character::player) {
			tp = true;
		}
		else {
			tp = false;
		}
		Bullet* bulletCpt = new Bullet((*bullet), angle, 300, 40, 3000, tp);
		bullet->AddComponent(bulletCpt);
		Vec2 bulletoffset(associated.box.w / 2, 0);
		bulletoffset = bulletoffset.Rotate(angle);
		bullet->box.x = (associated.box.Center().x + bulletoffset.x) - (bullet->box.w / 2);
		bullet->box.y = (associated.box.Center().y + bulletoffset.y) - (bullet->box.h / 2);
		bullet->angleDeg = ((angle * 360) / (2 * PI))+90;
		Game::GetInstance().GetState().AddObject(bullet);
		//b2
		GameObject* bullet2 = new GameObject();
		Bullet* bulletCpt2 = new Bullet((*bullet2), angle+(PI/8), 300, 40, 3000, tp);
		bullet2->AddComponent(bulletCpt2);
		bullet2->box.x = (associated.box.Center().x + bulletoffset.x) - (bullet2->box.w / 2);
		bullet2->box.y = (associated.box.Center().y + bulletoffset.y) - (bullet2->box.h / 2);
		bullet2->angleDeg = (((angle + (PI / 8)) * 360) / (2 * PI)) + 90;
		Game::GetInstance().GetState().AddObject(bullet2);
		//b3
		GameObject* bullet3 = new GameObject();
		Bullet* bulletCpt3 = new Bullet((*bullet3), angle - (PI / 8), 300, 40, 3000, tp);
		bullet3->AddComponent(bulletCpt3);
		bullet3->box.x = (associated.box.Center().x + bulletoffset.x) - (bullet3->box.w / 2);
		bullet3->box.y = (associated.box.Center().y + bulletoffset.y) - (bullet3->box.h / 2);
		bullet3->angleDeg = (((angle - (PI / 8)) * 360) / (2 * PI)) + 90;
		Game::GetInstance().GetState().AddObject(bullet3);
	}
	return;
}
