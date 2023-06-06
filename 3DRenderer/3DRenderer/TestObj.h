#pragma once
#include "GameObject.h"
#include "OBJ-Loader/OBJ_Loader.h"
#include "Material.h"
#include "RendererObject.h"
#include "UnmappedMat.h"
#include "ModelLoader.h"
class TestObj: public GameObject
{
public:
	TestObj() :objectMesh(am) {
		Start();
	}

	TestObj(float x, float y, float z) :objectMesh(am) {
		Start();
		ObjectTransform->xPos = x;
		ObjectTransform->yPos = y;
		ObjectTransform->zPos = z;
	}
	Mesh& objectMesh;
	RendererObject Renderer;
	
	void Start() {
		LoadMesh("test2.obj", am);
		Renderer.ObjectMesh = objectMesh;
		Renderer.ObjectTransform = ObjectTransform;
		Renderer.BaseMat = &mat;
	//	test();
	}

	void Update() {
		Renderer.Update();
		ObjectTransform->xRot += radians(1);
	}

private:
	
	Mesh am = Mesh();
	UnmappedMat mat = UnmappedMat();

//	MatrixMxN<float> t1 = MatrixMxN<float>(4096, 4096);
	//MatrixMxN<float> t2 = MatrixMxN<float>(4096, 4096);
};

