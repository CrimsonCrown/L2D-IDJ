#include "Sound.h"

Sound::Sound(){
	chunk=nullptr;
	return;
}

Sound::Sound(std::string file) : Sound(){
	Open(file);
	return;
}

Sound::~Sound(){
	Stop();
	return;
}

void Sound::Play(int times){
	channel=Mix_PlayChannel(-1,chunk,times-1);
	return;
}

void Sound::Stop(){
	if(chunk!=nullptr){
		Mix_HaltChannel(channel);
	}
	return;
}

void Sound::Open(std::string file){
	chunk=Resources::GetSound(file);
	return;
}

bool Sound::IsOpen(){
	if(chunk!=nullptr){
		return true;
	}
	return false;
}