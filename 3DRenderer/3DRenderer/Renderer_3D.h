#pragma once
#pragma warning(disable : 4996

#include <cstdio>
#include <iostream>
#include <vector>
#include "Bitmap.h"
#include "Backtracker.h"
#include <Windows.h>
#include "MatrixMxN.h"
#include <math.h>
#include "Mesh.h"
#include <thread>
#include <queue>
#include <unordered_map>
#include <mutex>
using namespace std;

// Refactor 3D class to only contain essentials needed for 3D and basic 2D rasterization.
// Img data is not part of class anymore, must pass pointer to bitmap class to use bitmaps and textures.
// Provides more support for more customizable/modularity effects and shaders.

void Texture_Setup(bitmap_image* textdata, float* parameters) {
	bitmap_image** tbmp = (bitmap_image**)parameters;
	*tbmp = textdata;
}

bitmap_image* TextData_Decode(float* parms) {
	bitmap_image** dec = (bitmap_image**)parms;
	return (*dec);
}

Triangle* Get_Triangle(float* parms) { // Pass in a starting pointer to the first fragment of the triangle. 
	// Usually its index 3 of vectors in fragshader.
	Triangle** tris = (Triangle**)parms;
	return (*tris);
}


struct ZBufferFrag {
	COLORREF colour;
	float z_index;
	int x, y;
};

class Renderer3D
{

public:

	void setCanvas(int resX, int resY) { // Create a canvas
		myconsole = GetConsoleWindow();
		maxWidth = resX; maxHeight = resY;
		//Get a handle to device context
	    mydc = GetDC(myconsole);
		memdc = CreateCompatibleDC(mydc);
		hbitmap = CreateCompatibleBitmap(mydc, resX, resY);
		SelectObject(memdc, hbitmap);
	}
	
	float checkTriangle(VectorCoords pt1, VectorCoords pt2, VectorCoords vtr) {  // Perform triangle inside test and generate Bcoords.
		const float a = pt2.y - pt1.y;
			const float b = pt1.x - pt2.x;
			const float c = pt2.x * pt1.y - pt1.x * pt2.y;

			const float val = a * vtr.x + b * vtr.y + c;

		return val;
	}

	int encodeXY(int x, int y) {
		int res = y * maxWidth + x;

		return res;
	}
	
	void ClearPixels() {
		
		for (auto x = zbuffer.begin(); x != zbuffer.end(); x++) {
			
			ZBufferFrag r = x->second;

			SetPixelV(memdc, r.x, r.y, RGB(0, 0, 0));
		}

		zbuffer.clear();
	}

	void SetPixelOptimized(HDC hdc, float x, float y, COLORREF colour) {
		int t = encodeXY(x, y);
		ZBufferFrag zfrag;
		zfrag.colour = colour;
		zfrag.z_index = 0;
		zfrag.x = x;
		zfrag.y = y;

		std::lock_guard<std::mutex> guard(zbuffer_m);

		if (zbuffer.find(t) != zbuffer.end()) {
			zbuffer[t].colour = colour;
			zbuffer[t].x = x; zbuffer[t].y = y;
			SetPixelV(hdc, x, y, colour);
		}
		else {
			std::pair<float, ZBufferFrag> pair(t, zfrag);
			zbuffer.insert(pair);
			SetPixelV(hdc, x, y, colour);
		}
	}

	void SetPixelZBuffer(HDC hdc, float x, float y, float z, COLORREF colour) {
		int t = encodeXY(x, y);
		ZBufferFrag zfrag;
		zfrag.colour = colour;
		zfrag.z_index = z;
		zfrag.x = x;
		zfrag.y = y;

		std::lock_guard<std::mutex> guard(zbuffer_m);
		if (zbuffer.find(t) != zbuffer.end()) {
			if (zbuffer[t].z_index < z) {
				
				zbuffer[t].z_index = z;
				zbuffer[t].colour = colour;
				zbuffer[t].x = x; zbuffer[t].y = y;

				SetPixelV(hdc, x, y, colour);
			}
			else {
				SetPixelV(hdc, x, y, zbuffer[t].colour);
			}
		}
		else {
			std::pair<float, ZBufferFrag> pair(t, zfrag);
			zbuffer.insert(pair);
			SetPixelV(hdc, x, y, colour);
		}
	}

	// take 3 vertices defining a solid triangle and rasterize to framebuffer. Requires function pointer that performs pixel shading and optional parameters (addparms)
	void RenderTris(Triangle t, Material* mat) {

		int maxX = 0;
		int minX = 0;

		int maxY = 0;
		int minY = 0;

	//	t.TruncatebyMaxMin(0, max(maxHeight, maxWidth));

		VectorCoords tester[3] = { t.v1, t.v2, t.v3 };
		for (int l = 0; l < 3;l++) {

			if (l == 0)
				maxX = tester[l].x;
			else if (maxX < tester[l].x)
				maxX = tester[l].x;
		}

		for (int l = 0; l < 3; l++) {
			if (l == 0)
				minX = tester[l].x;
			else if (minX > tester[l].x)
				minX = tester[l].x;
		}

		for (int l = 0; l < 3; l++) {

			if (l == 0)
				maxY = tester[l].y;
			else if (maxY < tester[l].y)
				maxY = tester[l].y;
		}

		for (int l = 0; l < 3; l++) {
			if (l == 0)
				minY = tester[l].y;
			else if (minY > tester[l].y)
				minY = tester[l].y;
		}

		
		const float mx = ceil((t.v1.x + t.v2.x + t.v3.x) / 3);
		const float my = ceil((t.v1.y + t.v2.y + t.v3.y) / 3);
		const float tarea = checkTriangle(t.v1, t.v2, VectorCoords(mx, my)) + checkTriangle(t.v2, t.v3, VectorCoords(mx, my)) + checkTriangle(t.v3, t.v1, VectorCoords(mx, my));

		if (minX < 0)
			minX = 0;
		if (minX > maxWidth)
			minX = maxWidth;

		if (maxX < 0)
			maxX = 0;
		if (maxX > maxWidth)
			maxX = maxWidth;

		if (minY < 0)
			minY = 0;
		if (minY > maxHeight)
			minY = maxHeight;

		if (maxY < 0)
			maxY = 0;
		if (maxY > maxHeight)
			maxY = maxHeight;
		
			if (mat != nullptr) {
				int xt = minX;
				int yt = minY;

#pragma omp parallel for private(xt,yt)
				for (xt = minX; xt <= maxX; xt++) {
					for (yt = minY; yt <= maxY; yt++) {
						const float ev1 = checkTriangle(t.v2, t.v3, VectorCoords(xt,yt));
						const float ev2 = checkTriangle(t.v3, t.v1, VectorCoords(xt, yt));
						const float ev3 = checkTriangle(t.v1, t.v2, VectorCoords(xt, yt));
						if (ev1 < 0 || ev2 < 0 || ev3 < 0) {
						}
						else {
							// Fragment shader code

							/*
					const rV = [(ev1 / tarea) * v1[2][0], (ev1 / tarea) * v1[2][1], (ev1 / tarea) * v1[2][2]]
					const gV = [(ev2 / tarea) * v2[2][0], (ev2 / tarea) * v2[2][1], (ev2 / tarea) * v2[2][2]]
					const bV = [(ev3 / tarea) * v3[2][0], (ev3 / tarea) * v3[2][1], (ev3 / tarea) * v3[2][2]]

					const res = [rV[0] + gV[0] + bV[0], rV[1] + gV[1] + bV[1], rV[2] + gV[2] + bV[2]]

							*/
							const float rV = (ev1 / tarea) * t.v1.r + (ev2 / tarea) * t.v2.r + (ev3 / tarea) * t.v3.r; // , (ev1 / tarea)* v1.b;
							const float gV = (ev1 / tarea) * t.v1.g + (ev2 / tarea) * t.v2.g + (ev3 / tarea) * t.v3.g;
							const float bV = (ev1 / tarea) * t.v1.b + (ev2 / tarea) * t.v2.b + (ev3 / tarea) * t.v3.b;

							// Baycentric coordinates for UV/Text/Normals
							const float vectors[] = {rV, gV, bV, 0,0}; // first 3 vectors are bcoords, the remaining are fragments to a pointer 
							// to the meshes's triangle.

							Triangle** trs = (Triangle**)(vectors + 3);
							(*trs) = &t;

							// Pass vertex information to the Material (which has a frag shader)
							mat->PassVectors(vectors);
							VectorCoords fragColor = mat->GetFragShader();

				//			if (xt <= minX + 3 || xt >= maxX-3 || yt >= maxY-3 || yt <= minY+3) {
					//			fragColor = VectorCoords(255, 0, 0);
						//	}
						//	SetPixelV(memdc, xt, yt, RGB(fragColor.x,fragColor.y,fragColor.z));

							if (rand() % 100 >= (100 - 50)) {
								SetPixelZBuffer(memdc, xt, yt, t.v1.z, RGB(fragColor.x, fragColor.y, fragColor.z));
							}
						//	SetPixelZBuffer(memdc, xt, yt, t.v1.z, RGB(fragColor.x, fragColor.y, fragColor.z));
						}
					}
				}
			}
	}
	
	void RenderScreenSpace(int Xcoord, int Ycoord, MatrixMxN<float> transform, bitmap_image* img = nullptr, VectorCoords(*fragShader)(const float[], const float[]) = nullptr, float* addparms = nullptr) { // Render directly to screenspace.
		// Supports the same fragment shader models as 3D. Fragment shader is optional.

		int offsetX = 0;
		int offsetY = 0;

		float Sx = 0;
		float Sy = 0;

		if (Sx <= 0)
			Sx = 1;

		if (Sy <= 0)
			Sy = 1;

		for (int i = 0; i < img->height(); i++) {
			for (int j = 0; j <img->width(); j++) {

				int sum = img->get_pixel(j, i).red + img->get_pixel(j, i).green + img->get_pixel(j, i).blue;
				if (sum < 765) {
					COLORREF COLOR = RGB(img->get_pixel(j, i).red, img->get_pixel(j, i).green, img->get_pixel(j, i).blue);
					//cout << "x,y: " << j << ", " << i  << " T(x,y): " << j + (sX)+offsetX << ", "<< i + (sY)+offsetY << '\n';

					// {1, 0}
					// {0, 1}

					// {a, b}(x)
					// {c, d}(y)

					// (cos(t)x + -sin(t)y, sin(t)x + cos(t)y)

					//(ax +by, cx+ dy)
					float x = j + offsetX;
					float y = i + offsetY;
					VectorCoords r = transform.matmul_vtr(VectorCoords(x, y));

					if (fragShader != nullptr) {
						const float v[] = { r.x, r.y };
						r = fragShader(v, addparms);
					}
					
					SetPixelV(memdc, r.x, r.y, COLOR);
				}
				//cout << maze[i][j] << "";
			//	cout << "\u001b[" << 40 + maze[i][j] << ";" << "1m" << " ";
				//cout << "\033[0m";
			}
			//std::cout << '\n';
		//	cout << "\033[0m";
		}
	}

	void deleteImage() {
		ReleaseDC(myconsole, memdc);
		DeleteObject(hbitmap);
	}

	void displayImage(int resX, int resY) { // Render image to buffer (Screen) with the desired canvas size
		BitBlt(mydc, 0, 0, resX, resY, memdc, 0, 0, SRCCOPY);
	}

	/*
	void rasterizepool(int poolID, bool* state) {
		while (*state) {
			if (sem[poolID] == 0 && pmain.size() > 0 && !pmain[poolID].empty()) {
				sem[poolID] = 1;
				RenderTris(pmain[poolID].top(), pmain[poolID].top().FragMaterial);
				pmain[poolID].pop();
				sem[poolID] = 0;
			}
		}
	}

	*/

private:
	HWND myconsole = GetConsoleWindow();
	int maxWidth = 0;
	int maxHeight = 0;
	
	//Get a handle to device context
	HDC mydc = GetDC(myconsole);
	HDC memdc = CreateCompatibleDC(mydc);
	HBITMAP hbitmap;
	//ZBufferFrag* zbuffer = nullptr;
	std::unordered_map<int, ZBufferFrag> zbuffer;
	std::mutex zbuffer_m;
};

