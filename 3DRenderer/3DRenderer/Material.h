#pragma once
#include "VectorCoords.h"
class Material
{
public:

	// All Material objects MUST implement all of the required Material methods.
	// Material name
	int MaterialID = 0;
	// Returns the fragment shader
	virtual VectorCoords GetFragShader() = 0;
	// The rasterizer passes polygon information about the mesh per fragment through this method.
	virtual void PassVectors(const float* vtrs) = 0;

};

// Sample functional frag shaders
/*
VectorCoords FragShader_BS(const float vectors[], const float parms[]) {

	return VectorCoords(255 * (vectors[0] + 1) / 2.0f, 255 * (vectors[1] + 1) / 2.0f, 255 * (vectors[2] + 1) / 2.0f);
}

VectorCoords FragShader_Text(const float vectors[], const float parms[]) {
	bitmap_image* im = TextData_Decode((float*)parms);

	int width = im->width() - 1; int height = im->height() - 1;

	rgb_t texel;
	texel.red = 255;
	texel.green = 255;
	texel.blue = 255;

	float uvx = ((vectors[0] + 1) / 2.0f);
	float uvy = ((vectors[1] + 1) / 2.0f);
	float uvz = ((vectors[2] + 1) / 2.0f);
	if (uvx >= 0 && uvx <= 1 && uvy >= 0 && uvy <= 1) {

		texel = im->get_pixel(width * uvx, height * uvy);
	}
	else if (uvx >= 0 && uvx <= 1 && uvz >= 0 && uvz <= 1) {
		texel = im->get_pixel(width * uvx, height * uvz);
	}
	else if (uvy >= 0 && uvy <= 1 && uvz >= 0 && uvz <= 1) {
		texel = im->get_pixel(width * uvy, height * uvz);
	}

	Triangle* x = Get_Triangle((float*)vectors + 3);
	return VectorCoords(texel.red, texel.green, texel.blue);
}

VectorCoords FragShader_White(const float vectors[], const float parms[]) {
	return VectorCoords(255, 255, 255);
}

VectorCoords FragShader_Red(const float vectors[], const float parms[]) {
	return VectorCoords(255, 0, 0);
}
*/
