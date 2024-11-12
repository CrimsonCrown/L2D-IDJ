#ifndef GAMEOBJECT_INCLUDE
#define GAMEOBJECT_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Rect.h"

class Component;

class GameObject{
public:
	GameObject();
	~GameObject();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	
	template<typename T>
	T* GetComponent(){
		long unsigned int index;
		for(index=0;index<components.size();index++){
			T* component = dynamic_cast<T*>(components[index].get());
			if(component != nullptr){
				return component;
			}
		}
		return nullptr;
	}

	Rect box;
	void Start();
	bool started;
	double angleDeg;
	int z;
private:
	std::vector<std::unique_ptr<Component>> components;
	bool isDead;
};

#endif