#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
	started=false;
	isDead=false;
	angleDeg=0;
	z = 0;
	return;
}

GameObject::~GameObject(){
	components.clear();
}

void GameObject::Update(float dt){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		//std::cout << "try updating cpt\n";
		components[index]->Update(dt);
		//std::cout << "finish updating cpt\n";
	}
	//std::cout << "finished updating GO\n";
	return;
}

void GameObject::Render(){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		components[index]->Render();
	}
	return;
}

bool GameObject::IsDead(){
	return isDead;
}

void GameObject::RequestDelete(){
	isDead=true;
	return;
}

void GameObject::AddComponent(Component* cpt){
	if(started){
		cpt->Start();
	}
	components.emplace_back(cpt);
	return;
}

void GameObject::RemoveComponent(Component* cpt){
	long unsigned int index;
	if (cpt == nullptr) {
		return;
	}
	for(index=0;index<components.size();index++){
		if(components[index].get()==cpt){
			components.erase(components.begin()+index);
		}
	}
	return;
}

void GameObject::Start(){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		components[index]->Start();
	}
	started=true;
	return;
}

void GameObject::NotifyCollision(GameObject& other) {
	long unsigned int index;
	index = 0;
	while(index < components.size()) {
		//std::cout << "before ncollision\n";
		components[index]->NotifyCollision(other);
		//std::cout << "after ncollision\n";
		index++;
	}
	//std::cout << "after ncollision loop\n";
	return;
}
