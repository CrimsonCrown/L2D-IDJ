#include "Gun.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "AnimationSetter.h"
#include "Bullet.h"

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
		if (cdtimer.Get() > 0.5) {
			cdtimer.Restart();
			if (associated.angleDeg > 90 || associated.angleDeg < -90) {
				associated.GetComponent<AnimationSetter>()->SetAnimation("reloadingFlip");
			}
			else {
				associated.GetComponent<AnimationSetter>()->SetAnimation("reloading");
			}
			reloadSound.Play(1);
			cooldown++;
		}
	}
	else if (cooldown == 2) {
		if (cdtimer.Get() > 0.5) {
			cdtimer.Restart();
			if (associated.angleDeg > 90 || associated.angleDeg < -90) {
				associated.GetComponent<AnimationSetter>()->SetAnimation("idleFlip");
			}
			else {
				associated.GetComponent<AnimationSetter>()->SetAnimation("idle");
			}
			cooldown++;
		}
	}
	else if (cooldown == 3) {
		if (cdtimer.Get() > 0.5) {
			cdtimer.Restart();
			cooldown=0;
		}
	}
	return;
}

void Gun::Render(){
	return;
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
			associated.GetComponent<AnimationSetter>()->SetAnimation("idleFlip");
		}
		else {
			associated.GetComponent<AnimationSetter>()->SetAnimation("idle");
		}
		std::cout << " t.x : " << target.x << " t.y : " << target.y << " center.x : " << ch->box.x << " center.y : " << ch->box.x << " incline : " << angle << " \n";
		cooldown = 1;
		cdtimer.Restart();
		shotSound.Play(1);
		//cria bullet
		GameObject* bullet = new GameObject();
		Bullet* bulletCpt = new Bullet((*bullet), angle, 600, 40, 3000);
		bullet->AddComponent(bulletCpt);
		Vec2 bulletoffset(associated.box.w / 2, 0);
		bulletoffset = bulletoffset.Rotate(angle);
		bullet->box.x = (associated.box.Center().x + bulletoffset.x) - (bullet->box.w / 2);
		bullet->box.y = (associated.box.Center().y + bulletoffset.y) - (bullet->box.h / 2);
		//2pi=360
		//angle=x
		//(angle*360)/2pi=x
		bullet->angleDeg = ((angle * 360) / (2 * PI))+90;
		Game::GetInstance().GetState().AddObject(bullet);
	}
	return;
}
