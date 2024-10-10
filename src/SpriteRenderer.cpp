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

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH) : Component(associated), sprite(file, frameCountW, frameCountH) {
	frameStart = 0;
	frameEnd = 0;
	frameTime = 0;
	currentFrame = 0;
	timeElapsed = 0;
	associated.box.w = sprite.GetWidth();
	associated.box.h = sprite.GetHeight();
	return;
}

void SpriteRenderer::Open(std::string file){
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
		timeElapsed += dt;
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
	sprite.Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h, associated.angleDeg);
}

bool SpriteRenderer::Is(std::string type) {
	if (type == "SpriteRenderer") {
		return true;
	}
	return false;
}

void SpriteRenderer::SetAnimation(Animation anim) {
	frameStart = anim.frameStart;
	frameEnd = anim.frameEnd;
	frameTime = anim.frameTime;
	currentFrame = frameStart;
	sprite.SetFrame(currentFrame);
	sprite.SetFlip(anim.flip);
	timeElapsed = 0;
}

void SpriteRenderer::SetCameraFollower(bool cf) {
	sprite.cameraFollower = cf;
}

void SpriteRenderer::SetScaleX(float scaleX, float scaleY) {
	Vec2 oldCenter = associated.box.Center();
	Vec2 oldScale = sprite.GetScale();
	sprite.SetScaleX(scaleX,scaleY);
	if (scaleX != 0) {
		float xmult = scaleX / oldScale.x;
		associated.box.w = associated.box.w*xmult;
	}
	if (scaleY != 0) {
		float ymult = scaleY / oldScale.y;
		associated.box.h = associated.box.h*ymult;
	}
	Vec2 newCenter = associated.box.Center();
	Vec2 diff = oldCenter.Sub(newCenter);
	associated.box = associated.box.Add(diff);
	return;
}
