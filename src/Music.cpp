#include "Music.h"
#include "Resources.h"

Music::Music(){
	music=nullptr;
	return;
}

Music::Music(const char* file){
	music=nullptr;
	Open(file);
	return;
}

void Music::Play(int times){
	if(music!=nullptr){
		Mix_PlayMusic(music,times);
	}
	else{
		std::cout << "no music loaded\n";
	}
	return;
}

void Music::Stop(int msToStop){
	Mix_FadeOutMusic(msToStop);
	std::cout << msToStop << " stop the musix\n";
	return;
}

void Music::Open(const char* file){
	//if(music!=nullptr){
		//Mix_FreeMusic(music);
	//}
	music= Resources::GetMusic(file);
	if(music==nullptr){
		std::cout << SDL_GetError();
	}
	return;
}

bool Music::IsOpen(){
	if(music!=nullptr){
		return true;
	}
	return false;
}

Music::~Music(){
	Stop();
	std::cout << "destroy the musix\n";
	//Mix_FreeMusic(music);
	return;
}