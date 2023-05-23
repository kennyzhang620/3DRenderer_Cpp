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
		ObjectTransform->xPos = x;
		ObjectTransform->yPos = y;
		ObjectTransform->zPos = z;
		Start();
	}
	void Start() {
		MainCamera.ObjectTransform = ObjectTransform;
	}
	void Update() {
		MainCamera.Update();

		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xPos += defaultX.x;
			ObjectTransform->yPos += defaultX.y;
			ObjectTransform->zPos += defaultX.z;

		}

		if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xPos -= defaultX.x;
			ObjectTransform->yPos -= defaultX.y;
			ObjectTransform->zPos -= defaultX.z;

		}

		if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xPos += defaultZ.x;
			ObjectTransform->yPos += defaultZ.y;
			ObjectTransform->zPos += defaultZ.z;

		}

		if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xPos -= defaultZ.x;
			ObjectTransform->yPos -= defaultZ.y;
			ObjectTransform->zPos -= defaultZ.z;

		}

		if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xPos += defaultY.x;
			ObjectTransform->yPos += defaultY.y;
			ObjectTransform->zPos += defaultY.z;

		}

		if (GetKeyState('Z') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			
			
			ObjectTransform->xPos -= defaultY.x;
			ObjectTransform->yPos -= defaultY.y;
			ObjectTransform->zPos -= defaultY.z;

		}

		if (GetKeyState('J') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xRot += radians(1);
			orientation.RotateX(radians(1));
			orientation.res_to_matrix();

			defaultZ = orientation.matmul_vtr(defaultZ);
			defaultY = orientation.matmul_vtr(defaultY);
			defaultX = orientation.matmul_vtr(defaultX);
		}

		if (GetKeyState('L') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->xRot -= radians(1);

			orientation.RotateX(radians(-1));
			orientation.res_to_matrix();

			defaultZ = orientation.matmul_vtr(defaultZ);
			defaultY = orientation.matmul_vtr(defaultY);
			defaultX = orientation.matmul_vtr(defaultX);
	
		}

		if (GetKeyState('I') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->yRot -= radians(1);

			orientation.RotateY(radians(-1));
			orientation.res_to_matrix();

			defaultZ = orientation.matmul_vtr(defaultZ);
			defaultY = orientation.matmul_vtr(defaultY);
			defaultX = orientation.matmul_vtr(defaultX);
			
		}

		if (GetKeyState('K') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			ObjectTransform->yRot += radians(1);

			orientation.RotateY(radians(1));
			orientation.res_to_matrix();

			defaultZ = orientation.matmul_vtr(defaultZ);
			defaultY = orientation.matmul_vtr(defaultY);
			defaultX = orientation.matmul_vtr(defaultX);
	
		}
	}

private:
	CameraObject cams = CameraObject(0.01f, 1000, Project_Perspective);
	MatrixMxN<float> orientation = MatrixMxN<float>(4, 4);
	VectorCoords defaultZ = VectorCoords(0, 0, 0.1f);
	VectorCoords defaultY = VectorCoords(0, 0.1f, 0);
	VectorCoords defaultX = VectorCoords(0.1f, 0, 0);
};

