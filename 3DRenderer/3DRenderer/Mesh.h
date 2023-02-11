#pragma once
#include <vector>
#include "VectorCoords.h"

using namespace std;

class Triangle {
public:
	VectorCoords v1;
	VectorCoords v2;
	VectorCoords v3;
	VectorCoords(*FragShader)(const float[], const float[]) = nullptr;
	float* fparms = nullptr; // Float array of parameters (actually bc its c/c++ u can encode whatever with pointers)

	float z_index; // For z-buffering

	// stores uv coordinates for texturing (often in conjunction with r,g,b,a above)

	float ux = 0;
	float uy = 0;

	bool operator > (const Triangle& str) const
	{
		return (z_index > str.z_index);
	}

	bool operator < (const Triangle& str) const
	{
		return (z_index < str.z_index);
	}

	Triangle(VectorCoords x, VectorCoords y, VectorCoords z) {
		v1 = x;
		v2 = y;
		v3 = z;
		FragShader = nullptr;
		z_index = max(v1.z, v2.z);
		z_index = max(z_index, v3.z);
	}

	Triangle(VectorCoords x, VectorCoords y, VectorCoords z, VectorCoords(*f1)(const float[], const float[])) {
		v1 = x;
		v2 = y;
		v3 = z;
		FragShader = f1;

		z_index = max(v1.z, v2.z);
		z_index = max(z_index, v3.z);
	}

	Triangle(VectorCoords x, VectorCoords y, VectorCoords z, float uvx, float uvy, VectorCoords(*f1)(const float[], const float[])) {
		v1 = x;
		v2 = y;
		v3 = z;
		ux = uvx;
		uy = uvy;
		FragShader = f1;

		z_index = max(v1.z, v2.z);
		z_index = max(z_index, v3.z);
	}

	Triangle(VectorCoords x, VectorCoords y, VectorCoords z, VectorCoords(*f1)(const float[], const float[]), float* addparms) {
		v1 = x;
		v2 = y;
		v3 = z;
		FragShader = f1;
		fparms = addparms;

		z_index = max(v1.z, v2.z);
		z_index = max(z_index, v3.z);
	}

	Triangle(VectorCoords x, VectorCoords y, VectorCoords z, float uvx, float uvy, VectorCoords(*f1)(const float[], const float[]), float* addparms) {
		v1 = x;
		v2 = y;
		v3 = z;
		ux = uvx;
		uy = uvy;
		FragShader = f1;
		fparms = addparms;

		z_index = max(v1.z, v2.z);
		z_index = max(z_index, v3.z);
	}


};

class Mesh {
public:
	vector<Triangle> MeshCoords;
	vector<VectorCoords>  Normals;
	vector<VectorCoords> UVCoords;

	Mesh(vector<float> pos, vector<float> norms, vector<float> uvs) {
		//	cout << pos.size()/9 << "SS\n";
		for (int i = 0; i < pos.size(); i += 9) {

			VectorCoords tvs = VectorCoords(pos[i], pos[i + 1], pos[i + 2], 1, pos[i], pos[i + 1], pos[i + 2], 1);
			tvs.nx = norms[i];
			tvs.ny = norms[i + 1];
			tvs.nz = norms[i + 2];
			tvs.nw = 1;
			VectorCoords tvs1 = VectorCoords(pos[i + 3], pos[i + 4], pos[i + 5], 1, pos[i + 3], pos[i + 4], pos[i + 5], 1);
			tvs1.nx = norms[i + 3];
			tvs1.ny = norms[i + 4];
			tvs1.nz = norms[i + 5];
			tvs1.nw = 1;
			VectorCoords tvs2 = VectorCoords(pos[i + 6], pos[i + 7], pos[i + 8], 1, pos[i + 6], pos[i + 7], pos[i + 8], 1);
			tvs2.nx = norms[i + 6];
			tvs2.ny = norms[i + 7];
			tvs2.nz = norms[i + 8];
			tvs2.nw = 1;

			MeshCoords.push_back(Triangle(tvs, tvs1, tvs2));
		}

		for (int i = 0; i < uvs.size() / 3; i++) {
			UVCoords.push_back(VectorCoords(uvs[i], uvs[i + 1], uvs[i + 2]));
		}
	}

};

class Transform {
public:
	float xPos = 0;
	float yPos = 0;
	float zPos = 0;
	float xRot = 0;
	float yRot = 0;
	float zRot = 0;
	float xScale = 1;
	float yScale = 1;
	float zScale = 1;
};