#pragma once
#include "GameObject.h"
#include "Material.h"

enum ProjectionMode {
	Project_Perspective,
	Project_Ortho
};

class CameraObject : public GameObject
{
public:
	CameraObject() {
		Start();
	}
	CameraObject(float nP, float fP, ProjectionMode PM) {
		nearPlane = nP; farPlane = fP; ProjectMode = PM;
	}

	CameraObject(int x, int y, float nP, float fP, ProjectionMode PM) {
		ScreenX = x;
		ScreenY = y;
		nearPlane = nP; farPlane = fP; ProjectMode = PM;
	}

	int ScreenX = windowX;
	int ScreenY = windowY;

	float nearPlane = 0.01f;
	float farPlane = 1000;

	ProjectionMode ProjectMode = Project_Perspective;
	void Update() {
		CameraSetup(ScreenX, ScreenY, *ObjectTransform, nearPlane, farPlane, ProjectMode);
	}

};

