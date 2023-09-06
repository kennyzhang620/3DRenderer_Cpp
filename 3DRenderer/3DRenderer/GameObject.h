#pragma once
#include "Global_Stack.h"
class GameObject
{
public:

	Transform* ObjectTransform;

	GameObject() {
		ObjectTransform = &def;
	}

	GameObject(float x, float y, float z) {
		ObjectTransform = &def;
		
		ObjectTransform->xPos = x;
		ObjectTransform->yPos = y;
		ObjectTransform->zPos = z;
	}
	// Called once upon instantiation
	virtual void Start() = 0;

	void OnEnable() {

	}

	void OnDisable() {

	}
	
	// Called per frame
	virtual void Update() = 0;

private:
	Transform def = Transform();
};

