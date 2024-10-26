#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(){
	texture=nullptr;
	frameCountW = 1;
	frameCountH = 1;
	cameraFollower = false;
	flip = SDL_FLIP_NONE;
	SetScale(1,1);
	return;
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH){
	texture=nullptr;
	cameraFollower = false;
	//std::cout << "w1: " << frameCountW << " h1: " << frameCountH << "\n";
	this->frameCountW = frameCountW;
	this->frameCountH = frameCountH;
	flip = SDL_FLIP_NONE;
	SetScale(1, 1);
	Open(file);
	//std::cout << "w2: " << this->frameCountW << " h2: " << this->frameCountH << "\n";
	return;
}

Sprite::~Sprite(){
	return;
}

void Sprite::Open(std::string file){
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetFrame(0);
	return;
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect.x=x;
	clipRect.y=y;
	clipRect.w=w;
	clipRect.h=h;
	return;
}

void Sprite::Render(int x, int y, int w, int h, float angle){
	SDL_Rect dstrect;
	if (cameraFollower) {
		dstrect.x = x;
		dstrect.y = y;
	}
	else {
		dstrect.x = x - Camera::pos.x;
		dstrect.y = y - Camera::pos.y;
	}
	dstrect.w=w;
	dstrect.h=h;
	Game& instance = Game::GetInstance();
	SDL_RenderCopyEx(instance.GetRenderer(), texture, &clipRect, &dstrect, angle, nullptr, flip);
	return;
}

int Sprite::GetWidth() {
	return (width*scale.x) / frameCountW;
}

int Sprite::GetHeight() {
	return (height*scale.y) / frameCountH;
}

bool Sprite::IsOpen(){
	if(texture!=nullptr){
		return true;
	}
	return false;
}

void Sprite::SetFrame(int frame) {
	if (frame >= frameCountW*frameCountH) {
		std::cout << "frame out of range\n";
		return;
	}
	int result = frame / frameCountW;
	//int result = 0;
	int remainder = frame % frameCountW;
	//int remainder = 0;
	int offsetx = remainder * GetWidth();
	int offsety = result * GetHeight();
	SetClip(offsetx,offsety,GetWidth(),GetHeight());
	//std::cout << "result: " << frameCountW << " remainder: " << frameCountH << "\n";
	//std::cout << "result: " << result << " remainder: " << remainder << "\n";
	//SetClip(0, 0, 1200, 450);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
	this->frameCountW = frameCountW;
	this->frameCountH = frameCountH;
}

void Sprite::SetScale(float scaleX, float scaleY) {
	if (scaleX != 0) {
		scale.x = scaleX;
	}
	if (scaleY != 0) {
		scale.y = scaleY;
	}
	return;
}

Vec2 Sprite::GetScale() {
	return scale;
}

void Sprite::SetFlip(SDL_RendererFlip flip) {
	this->flip = flip;
}