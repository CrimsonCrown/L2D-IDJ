#include "AnimationSetter.h"
#include "SpriteRenderer.h"

AnimationSetter::AnimationSetter(GameObject& associated) : Component(associated){
	return;
}

void AnimationSetter::Update(float dt){
	return;
}

void AnimationSetter::Render(){
	return;
}

bool AnimationSetter::Is(std::string type){
	if(type=="AnimationSetter"){
		return true;
	}
	return false;
}

void AnimationSetter::AddAnimation(std::string name, Animation anim) {
	if (animations.find(name) == animations.end()) {
		animations.insert({ name,anim });
	}
	return;
}

void AnimationSetter::SetAnimation(std::string name) {
	if (animations.find(name) != animations.end()) {
		associated.GetComponent<SpriteRenderer>()->SetAnimation(animations.at(name));
	}
}