#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "SpriteRenderer.h"
#include "GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated), sprite() {
	frameStart = 0;
	frameEnd = 0;
	frameTime = 0;
	currentFrame = 0;
	timeElapsed = 0;
	return;
}

SpriteRenderer::SpriteRenderer(GameObject& associated, const char* file, int frameCountW, int frameCountH) : Component(associated), sprite(file, frameCountW, frameCountH) {
	frameStart = 0;
	frameEnd = 0;
	frameTime = 0;
	currentFrame = 0;
	timeElapsed = 0;
	associated.box.w = sprite.GetWidth();
	associated.box.h = sprite.GetHeight();
	return;
}

void SpriteRenderer::Open(const char* file){
	sprite.Open(file);
	associated.box.w = sprite.GetWidth();
	associated.box.h = sprite.GetHeight();
	return;
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
	sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Update(float dt) {
	if (frameTime != 0) {
		timeElapsed += 1;
		if (timeElapsed > frameTime) {
			timeElapsed -= frameTime;
			currentFrame += 1;
			if (currentFrame > frameEnd) {
				currentFrame = frameStart;
			}
			sprite.SetFrame(currentFrame);
		}
	}
	return;
}

void SpriteRenderer::Render(){
	sprite.Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}

void SpriteRenderer::SetAnimation(Animation anim) {
	frameStart = anim.frameStart;
	frameEnd = anim.frameEnd;
	frameTime = anim.frameTime;
	currentFrame = frameStart;
	sprite.SetFrame(currentFrame);
	timeElapsed = 0;
}