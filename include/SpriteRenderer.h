#ifndef SPRITERENDERER_INCLUDE
#define SPRITERENDERER_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Sprite.h"
#include "Component.h"
#include "Animation.h"

class SpriteRenderer : public Component {
public:
	SpriteRenderer(GameObject& associated);
	SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
	void Open(std::string file);
	void SetFrameCount(int frameCountW, int frameCountH);
	void Update(float dt);
	void Render();
	void SetAnimation(Animation anim);
	void SetCameraFollower(bool cf);
	void SetScaleX(float scaleX, float scaleY);
private:
	Sprite sprite;
	int frameStart;
	int frameEnd;
	float frameTime;
	int currentFrame;
	float timeElapsed;
};

#endif