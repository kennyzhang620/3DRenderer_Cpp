#pragma once
#include "Material.h"
class UnmappedMat :
    public Material
{

public:

	UnmappedMat() {

	}
	// Material name=
	int MaterialID = 0;
	// Returns the fragment shader
	virtual VectorCoords GetFragShader() override {
		return _fragShader(vectorPass, params);
	}
	// The rasterizer passes polygon information about the mesh per fragment through this method.
	virtual void PassVectors(const float* vtrs) override {
		vectorPass = (float*)vtrs;
	}

private:
	float* vectorPass;
	float params[2] = { 0,0 };

	VectorCoords _fragShader(const float vectors[], const float parms[]) {
		return VectorCoords(255 * (vectors[0] + 1) / 2.0f, 255 * (vectors[1] + 1) / 2.0f, 255 * (vectors[2] + 1) / 2.0f);
	}

};

