#pragma once
#include "GameObject.h"
#include "RendererObject.h"
class DebugSp: public GameObject
{
public:

	DebugSp():objectMesh(am) {
		Start();
	}

	DebugSp(float x, float y, float z) :objectMesh(am) {
		Start();
		ObjectTransform->xPos = x;
		ObjectTransform->yPos = y;
		ObjectTransform->zPos = z;
	}

	Mesh& objectMesh;
	RendererObject Renderer;

	void Start() {
		Renderer.ObjectMesh = objectMesh;
		Renderer.ObjectTransform = ObjectTransform;
	}
	void Update() {
		Renderer.Update();
	}

private:
	vector<float> positions = { -1,0,0, 1,0,0, 0,1,0}; //[-1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, 1, 1, 1, -1, 1, -1, -1, -1, -1, -1, 1, 1, -1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1, -1, -1, -1, 1, -1, -1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1, -1, 1, -1, 1, 1, -1]//[-1,-1,-1, -1,-1, 1, -1, 1, 1,   1, 1,-1, -1,-1,-1, -1, 1,-1,   1,-1, 1, -1,-1,-1, 1,-1,-1,   1, 1,-1, 1,-1,-1, -1,-1,-1, -1,-1,-1, -1, 1, 1, -1, 1,-1, 1,-1, 1, -1,-1, 1, -1,-1,-1, -1, 1, 1, -1,-1, 1, 1,-1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1,-1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, -1, 1,-1, 1, 1, 1, -1, 1,-1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1,-1, 1};
	vector<float> normals = { 0, 1, 0, 0,1,0,0,1,0};
	vector<float> test_norms = { 1, 0, 0};
	vector<float> uvCoords = {};
	vector<float> uv_test = {};

	Mesh am = Mesh(positions, normals, uvCoords);
};

