#pragma once
#include "Global_Stack.h"
class GameObject
{
public:

	Transform* ObjectTransform;

	GameObject() {
		Start();
		ObjectTransform = &def;
	}

	GameObject(float x, float y, float z) {
		Start();
		ObjectTransform = &def;
		
		ObjectTransform->xPos = x;
		ObjectTransform->yPos = y;
		ObjectTransform->zPos = z;
	}
	// Called once upon instantiation
	void Start() {

	}

	void OnEnable() {

	}

	void OnDisable() {

	}
	
	// Called per frame
	void Update() {

	}

private:
	Transform def = Transform();
};

