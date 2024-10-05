#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(){
	texture=nullptr;
	frameCountW = 1;
	frameCountH = 1;
	return;
}

Sprite::Sprite(const char* file, int frameCountW, int frameCountH){
	texture=nullptr;
	//std::cout << "w1: " << frameCountW << " h1: " << frameCountH << "\n";
	this->frameCountW = frameCountW;
	this->frameCountH = frameCountH;
	Open(file);
	//std::cout << "w2: " << this->frameCountW << " h2: " << this->frameCountH << "\n";
	return;
}

Sprite::~Sprite(){
	if(texture!=nullptr){
		SDL_DestroyTexture(texture);
	}
	return;
}

void Sprite::Open(const char* file){
	if(texture!=nullptr){
		SDL_DestroyTexture(texture);
	}
	texture=IMG_LoadTexture(Game::GetInstance().GetRenderer(),file);
	if(texture==nullptr){
		std::cout << SDL_GetError();
	}
	SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
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

void Sprite::Render(int x, int y, int w, int h){
	SDL_Rect dstrect;
	dstrect.x=x;
	dstrect.y=y;
	dstrect.w=w;
	dstrect.h=h;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstrect);
	return;
}

int Sprite::GetWidth(){
	return width/frameCountW;
}

int Sprite::GetHeight(){
	return height/frameCountH;
}

bool Sprite::IsOpen(){
	if(texture!=nullptr){
		return true;
	}
	return false;
}

void Sprite::SetFrame(int frame) {
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