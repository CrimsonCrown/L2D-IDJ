#include "AnimationSetter.h"
#include "SpriteRenderer.h"

AnimationSetter::AnimationSetter(GameObject& associated) : Component(associated){
	frameStart = 0;
	frameEnd = 0;
	frameTime = 0;
	currentFrame = 0;
	timeElapsed = 0;
	return;
}

void AnimationSetter::Update(float dt){
	if (frameTime != 0) {
		timeElapsed += dt;
		if (timeElapsed > frameTime) {
			timeElapsed -= frameTime;
			currentFrame += 1;
			if (currentFrame > frameEnd) {
				currentFrame = frameStart;
			}
			((SpriteRenderer*)associated.GetComponent("SpriteRenderer"))->SetFrame(currentFrame, animations.at(current).flip);
		}
	}
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
		if (current != name) {
			current = name;
			//((SpriteRenderer*)associated.GetComponent("SpriteRenderer"))->SetAnimation(animations.at(name));
			Animation anim = animations.at(name);
			frameStart = anim.frameStart;
			frameEnd = anim.frameEnd;
			frameTime = anim.frameTime;
			currentFrame = frameStart;
			//sprite.SetFrame(currentFrame);
			((SpriteRenderer*)associated.GetComponent("SpriteRenderer"))->SetFrame(currentFrame,anim.flip);
			//sprite.SetFlip(anim.flip);
			timeElapsed = 0;
		}
	}
}