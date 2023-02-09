#pragma once
#include <tgmath.h>
#include <random>
#include <iostream>

class VectorCoords {
public:
	// stores main vectors used for transformations
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;

	// stores original mesh coordinates in model space (r,g,b,a values for Barycentric, also for texturing)
	float r = 1;
	float g = 1;
	float b = 1;
	float a = 1;

	// stores normal information for lighting

	float nx = 0;
	float ny = 0;
	float nz = 0;
	float nw = 0;

	bool operator > (const VectorCoords& str) const
	{
		return (x > str.x);
	}

	bool operator < (const VectorCoords& str) const
	{
		return (x < str.x);
	}

	float norm() {
		return sqrtf(pow(x, 2) + pow(y, 2));
	}

	VectorCoords() {
		x = 0;
		y = 0;
		w = 1;
		r = 1;
		g = 1;
		b = 1;
		a = 1;
	}

	VectorCoords(float a, float b) {
		x = a;
		y = b;
		z = 0;
		w = 1;
		r = 1;
		g = 1;
		b = 1;
		a = 1;
	}

	VectorCoords(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
		w = 1;
		r = 1;
		g = 1;
		b = 1;
		a = 1;
	}

	VectorCoords(float a, float b, float c, float d) {
		x = a;
		y = b;
		z = c;
		w = d;
		r = 1;
		g = 1;
		b = 1;
		a = 1;
	}

	VectorCoords(float a, float b, float c, float d, float x1, float x2, float x3, float x4) {
		x = a;
		y = b;
		z = c;
		w = d;
		r = x1;
		g = x2;
		b = x3;
		a = x4;
	}


	~VectorCoords() {
		x = 0;
		y = 0;
	}

	VectorCoords zero() {
		VectorCoords init;

		return init;
	}
};




