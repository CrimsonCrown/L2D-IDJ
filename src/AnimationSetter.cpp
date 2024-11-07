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