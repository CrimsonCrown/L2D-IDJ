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