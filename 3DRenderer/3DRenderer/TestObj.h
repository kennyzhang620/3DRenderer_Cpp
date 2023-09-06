#pragma once
#include "GameObject.h"
#include "OBJ-Loader/OBJ_Loader.h"
#include "Material.h"
#include "RendererObject.h"
#include "UnmappedMat.h"
#include "ModelLoader.h"

// function pointer example:

float randVal(float seed) {
	return (float)(1 / seed);
}

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
	
	float(*test2)(float val);

	void test(float(*test)(float val)) {
		float a = test(0.0001);

		ObjectTransform->xRot += a;
	}
	
	void Start() {
		LoadMesh("test2.obj", am);
		Renderer.ObjectMesh = &objectMesh;
		Renderer.ObjectTransform = ObjectTransform;
		df.TextureMode = 1;
		df.TextureName = "testmodels/BED.bmp";
		Renderer.BaseMat = &df;
	//	test();
		test2 = nullptr;
	}

	void Update() {
		Renderer.Update();
		ObjectTransform->xRot += radians(1);
//		test(randVal);
	}

private:
	
	Mesh am = Mesh();
	DiffuseMaterial df = DiffuseMaterial();
	UnmappedMat m = UnmappedMat();
//	MatrixMxN<float> t1 = MatrixMxN<float>(4096, 4096);
	//MatrixMxN<float> t2 = MatrixMxN<float>(4096, 4096);
};

