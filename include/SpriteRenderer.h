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
	SpriteRenderer(GameObject& associated, const char* file, int frameCountW = 1, int frameCountH = 1);
	void Open(const char* file);
	void SetFrameCount(int frameCountW, int frameCountH);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void SetAnimation(Animation anim);
private:
	Sprite sprite;
	int frameStart;
	int frameEnd;
	float frameTime;
	int currentFrame;
	float timeElapsed;
};

#endif