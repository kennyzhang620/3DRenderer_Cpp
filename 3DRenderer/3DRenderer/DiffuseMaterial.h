#pragma once
#include "Material.h"
class DiffuseMaterial :
    public Material
{
public:

	string TextureName;
	char* textd = nullptr;
	char TextureMode = 0; // 0 Untextured 1 Basic texturing

	DiffuseMaterial() {
		vectorPass = nullptr;
		MaterialID = 1;
	}

	// Returns the fragment shader
	VectorCoords GetFragShader() override {
		return _fragShader2(vectorPass, params);
	}
	// The rasterizer passes polygon information about the mesh per fragment through this method.
	void PassVectors(const float* vtrs) override {
		vectorPass = (float*)vtrs;
		if (TextureName.c_str() != textd) {
			img = bitmap_image(TextureName);
			textd = (char*) TextureName.c_str();
		}
		Texture_Setup(&img, params);
	}

private:
	float* vectorPass;
	float params[2] = { 0,0 };
	bitmap_image img;

	VectorCoords _fragShader2(const float vectors[], const float parms[]) {
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

};

