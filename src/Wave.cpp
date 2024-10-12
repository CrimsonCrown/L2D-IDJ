#include "Wave.h"

Wave::Wave(int zombies, float cooldown, int npcs, float npccooldown){
	this->zombies = zombies;
	this->cooldown = cooldown;
	this->npcs = npcs;
	this->npccooldown = npccooldown;
	return;
}