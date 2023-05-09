#pragma once
#include "VectorCoords.h"
#include "FragmentShaders.h"
#include "VertexShader.h"
class Material
{
public:

	// Returns the fragment shader

	VectorCoords Mat_FragShader(const float vectors[], const float parms[]) {
		return VectorCoords(255, 0, 0);
	}
	
	float* GetFragParams() {
		return params;
	}
private:
	float params[2] = { 0,0 };
};

