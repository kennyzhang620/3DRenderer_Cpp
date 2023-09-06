#pragma once
#include <vector>
#include "Material.h"
#define T_POSITION 0 
#define T_ROTATION 1
#define T_SCALE 2

using namespace std;

class Triangle {
public:
	VectorCoords v1;
	VectorCoords v2;
	VectorCoords v3;
	Material* FragMaterial;
//	VectorCoords(*FragShader)(const float[], const float[]) = nullptr;
//	float* fparms = nullptr; // Float array of parameters (actually bc its c/c++ u can encode whatever with pointers)

	float z_index; // For z-buffering

	bool operator > (const Triangle& str) const
	{
		return (z_index > str.z_index);
	}

	bool operator < (const Triangle& str) const
	{
		return (z_index < str.z_index);
	}

	void TruncatebyMaxMin(float minV, float maxV) {
		if (v1.x < minV) {
			v1.x = minV;
		}

		if (v1.y < minV) {
			v1.y = minV;
		}

		if (v1.z < minV) {
			v1.z = minV;
		}

		if (v2.x < minV) {
			v2.x = minV;
		}

		if (v2.y < minV) {
			v2.y = minV;
		}

		if (v2.z < minV) {
			v2.z = minV;
		}

		if (v2.z < minV) {
			v2.z = minV;
		}

		if (v3.x < minV) {
			v3.x = minV;
		}

		if (v3.y < minV) {
			v3.y = minV;
		}

		if (v3.z < minV) {
			v3.z = minV;
		}


		if (v1.x > maxV) {
			v1.x = maxV;
		}

		if (v1.y > maxV) {
			v1.y = maxV;
		}

		if (v1.z > maxV) {
			v1.z = maxV;
		}

		if (v2.x > maxV) {
			v2.x = maxV;
		}

		if (v2.y > maxV) {
			v2.y = maxV;
		}

		if (v2.z > maxV) {
			v2.z = maxV;
		}

		if (v2.z > maxV) {
			v2.z = maxV;
		}

		if (v3.x > maxV) {
			v3.x = maxV;
		}

		if (v3.y > maxV) {
			v3.y = maxV;
		}

		if (v3.z > maxV) {
			v3.z = maxV;
		}
	}

	Triangle() {
//		FragShader = nullptr;
		FragMaterial = nullptr;
		z_index = 0;
	}

	Triangle(VectorCoords x, VectorCoords y, VectorCoords z) {
		v1 = x;
		v2 = y;
		v3 = z;
	//	FragShader = nullptr;
		FragMaterial = nullptr;
		z_index = min(min(v1.z, v2.z), v3.z);
	}

	Triangle(VectorCoords x, VectorCoords y, VectorCoords z,  Material* fl) {
		v1 = x;
		v2 = y;
		v3 = z;

		FragMaterial = fl;

		z_index = min(min(v1.z, v2.z), v3.z);

	}

};

class Mesh {
public:
	vector<Triangle> MeshCoords;
	vector<VectorCoords>  Normals;
	vector<VectorCoords> UVCoords;

	Mesh() {

	}

	Mesh(const char* objfile) {

	}

	void AddVertex(VectorCoords v, VectorCoords v2, VectorCoords v3) {

	}
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
	bool Update = true;

	Transform() {
	}

	void set_all(const Transform str) {
		xPos = str.xPos;
		yPos = str.yPos;
		zPos = str.zPos;

		xRot = str.xRot;
		yRot = str.yRot;
		zRot = str.zRot;

		xScale = str.xScale;
		yScale = str.yScale;
		zScale = str.zScale;
	}
	Transform operator + (const Transform& str) {
		return Transform(xPos + str.xPos, yPos + str.yPos, zPos + str.zPos,xRot + str.xRot,yRot + str.yRot,zRot + str.zRot,xScale + str.xScale,yScale + str.yScale,zScale + str.zScale);
	}

	Transform operator - (const Transform& str) {
		return Transform(xPos - str.xPos, yPos - str.yPos, zPos - str.zPos, xRot - str.xRot, yRot - str.yRot, zRot - str.zRot, xScale - str.xScale, yScale - str.yScale, zScale - str.zScale);
	}

	Transform operator * (const Transform& str) {
		return Transform(xPos * str.xPos, yPos * str.yPos, zPos * str.zPos, xRot * str.xRot, yRot * str.yRot, zRot * str.zRot, xScale * str.xScale, yScale * str.yScale, zScale * str.zScale);

	}

	Transform operator / (const Transform& str) {
		return Transform(xPos / str.xPos, yPos / str.yPos, zPos / str.zPos, xRot / str.xRot, yRot / str.yRot, zRot / str.zRot, xScale / str.xScale, yScale / str.yScale, zScale / str.zScale);

	}

	VectorCoords GetVector() {
		return VectorCoords(xPos, yPos, zPos, xRot, yRot, zRot, xScale, yScale, zScale, 0);
	}

	float dot(const Transform& str) {
		return xPos * str.xPos + yPos * str.yPos + zPos * str.zPos;
	}

	Transform(float x, float y, float z, int MODE) {
		if (MODE == 0) {
			xPos = x; yPos = y; zPos = z;
		}
		
		if (MODE == 1) {
			xRot = x; yRot = y; zRot = z;
		}

		if (MODE == 2) {
			xScale = x; yScale = y; zScale = z;
		}
	}

	Transform(float x, float y, float z, float rx, float ry, float rz) {
			xPos = x; yPos = y; zPos = z;
			xRot = rx; yRot = ry; zRot = rz;
	}

	Transform(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz) {
		xPos = x; yPos = y; zPos = z;
		xRot = rx; yRot = ry; zRot = rz;
		xScale = sx; yScale = sy; zScale = sz;
	}
	
	void SetPosition(float x, float y, float z) {
		xPos = x; yPos = y; zPos = z;
	}

	void SetRotation(float x, float y, float z) {
		xRot = x; yRot = y; zRot = z;
	}

	void SetScale(float x, float y, float z) {
		xScale = x; yScale = y; zScale = z;
	}
};