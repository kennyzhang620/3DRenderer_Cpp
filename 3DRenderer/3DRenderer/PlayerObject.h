#pragma once
#include "GameObject.h"
#include "CameraObject.h"
class PlayerObject : public GameObject
{
public:
	CameraObject& MainCamera;

	PlayerObject() :MainCamera(cams) {
		Start();
	}

	PlayerObject(float x, float y, float z):MainCamera(cams) {
		GameObject(x, y, z);
		Start();
	}
	void Start() {
		MainCamera.ObjectTransform = ObjectTransform;
	}
	void Update() {
		MainCamera.Update();

		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xPos += 0.1f;

		}

		if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xPos -= 0.1f;

		}

		if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->zPos += 0.1f;

		}

		if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->zPos -= 0.1f;

		}

		if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->yPos += 0.1f;

		}

		if (GetKeyState('Z') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->yPos -= 0.1f;

		}

		if (GetKeyState('J') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xRot += radians(1);

		}

		if (GetKeyState('L') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xRot -= radians(1);
	
		}

		if (GetKeyState('I') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->yRot -= radians(1);
			
		}

		if (GetKeyState('K') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->yRot += radians(1);
	
		}
	}

private:
	CameraObject cams = CameraObject(0.01f, 1000, Project_Perspective);
};

