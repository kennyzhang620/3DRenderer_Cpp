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

using namespace std;

class BMPLib
{

public:
	unsigned int readPixelAt(int i, int j, int pos) {
			if (pos == 0) {
				return img.get_pixel(i, j).red;
			}
			if (pos == 1) {
				return img.get_pixel(i, j).green;
			}
			if (pos == 2) {
				return img.get_pixel(i, j).blue;
			}
	}

	void writePixelAt(int i, int j, int r, int g, int b) {
		rgb_t colours;

		colours.red = r;
		colours.green = g;
		colours.blue = b;
		img.set_pixel(i, j, colours);
	}

	void read(const char* filename) {
		readImg(filename);
	}

	VectorCoords getDimensions() {
		VectorCoords dim;
		dim.x = img.width();
		dim.y = img.height();

		return dim;
	}

	VectorCoords startPos() {
		VectorCoords start;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				//	std::cout << "(" << x << "," << y << ") =>" << "RGB(" << (unsigned int) data[3 * (x * width + y)] << "," << (unsigned int) data[3 * (x * width + y) + 1] << "," << (unsigned int) data[3 * (x * width + y) + 2] << ")\n";
				if (img.get_pixel(x, y).red <= 50 && img.get_pixel(x, y).green <= 50 && img.get_pixel(x, y).blue >= 200) {
					start.x = x;
					start.y = y;

					return start;
				}
				else {
				}
			}
		}

		return start;
	}

	VectorCoords endPos() {
		VectorCoords end;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				//	std::cout << "(" << x << "," << y << ") =>" << "RGB(" << (unsigned int) data[3 * (x * width + y)] << "," << (unsigned int) data[3 * (x * width + y) + 1] << "," << (unsigned int) data[3 * (x * width + y) + 2] << ")\n";
				if (img.get_pixel(x, y).red <= 50 && img.get_pixel(x, y).green >= 200 && img.get_pixel(x, y).blue <= 50) {
					end.x = x;
					end.y = y;

					return end;
				}
				else {
				}
			}
		}

		return end;
	}

	void setCanvas(int resX, int resY) { // Create a canvas
		memdc = CreateCompatibleDC(mydc);
		hbitmap = CreateCompatibleBitmap(mydc, resX, resY);
		SelectObject(memdc, hbitmap);
	}
	
	float checkTriangle(VectorCoords pt1, VectorCoords pt2, VectorCoords vtr) {
		const float a = pt2.y - pt1.y;
			const float b = pt1.x - pt2.x;
			const float c = pt2.x * pt1.y - pt1.x * pt2.y;

			const float val = a * vtr.x + b * vtr.y + c;

		return val;
	}

	// take 3 vertices defining a solid triangle and rasterize to framebuffer. Requires function pointer that performs pixel shading and optional parameters (addparms)
	void RenderTris(VectorCoords v1, VectorCoords v2, VectorCoords v3, VectorCoords(*fragShader)(const float[], const float[]), float* addparms = nullptr) {

		int maxX = 0;
		int minX = 0;

		int maxY = 0;
		int minY = 0;

		VectorCoords tester[3] = { v1, v2, v3 };
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

		const float mx = ceil((v1.x + v2.x + v3.x) / 3);
		const float my = ceil((v1.y + v2.y + v3.y) / 3);
		const float tarea = checkTriangle(v1, v2, VectorCoords(mx, my)) + checkTriangle(v2, v3, VectorCoords(mx, my)) + checkTriangle(v3, v1, VectorCoords(mx, my));

			if (true) {
				for (int xt = minX; xt <= maxX; xt++) {
					for (int yt = minY; yt <= maxY; yt++) {
						const float ev1 = checkTriangle(v2, v3, VectorCoords(xt,yt));
						const float ev2 = checkTriangle(v3, v1, VectorCoords(xt, yt));
						const float ev3 = checkTriangle(v1, v2, VectorCoords(xt, yt));
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
							const float rV = (ev1 / tarea) * v1.r + (ev2 / tarea) * v2.r + (ev3 / tarea) * v3.r; // , (ev1 / tarea)* v1.b;
							const float gV = (ev1 / tarea) * v1.g + (ev2 / tarea) * v2.g + (ev3 / tarea) * v3.g;
							const float bV = (ev1 / tarea) * v1.b + (ev2 / tarea) * v2.b + (ev3 / tarea) * v3.b;

							// Baycentric coordinates for UV/Text/Normals
							const float vectors[] = { rV, gV, bV };
							const VectorCoords fragColor = fragShader(vectors, addparms);

							SetPixelV(memdc, xt, yt, RGB(255*fragColor.x,255*fragColor.y,255*fragColor.z));
						}
					}
				}
			}
	}
	
	void renderImage(int Xcoord, int Ycoord, MatrixMxN<float> transform) {

		int offsetX = 0;
		int offsetY = 0;

		float Sx = 0;
		float Sy = 0;

		if (Sx <= 0)
			Sx = 1;

		if (Sy <= 0)
			Sy = 1;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {

				int sum = img.get_pixel(j, i).red + img.get_pixel(j, i).green + img.get_pixel(j, i).blue;
				if (sum < 765) {
					COLORREF COLOR = RGB(img.get_pixel(j, i).red, img.get_pixel(j, i).green, img.get_pixel(j, i).blue);
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

	void clearImage(int width, int height) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				COLORREF COLOR = RGB(0, 0, 0);
				SetPixelV(memdc, j, i, COLOR);
			}
		}
	}

	void clearScreen(int Xcoord, int Ycoord) {

		int offsetX = 0;
		int offsetY = 0;

		for (int i = 0; i < Ycoord; i++) {
			for (int j = 0; j < Xcoord; j++) {

					COLORREF COLOR = RGB(0, 0, 0);
					//cout << "x,y: " << j << ", " << i  << " T(x,y): " << j + (sX)+offsetX << ", "<< i + (sY)+offsetY << '\n';

					// {1, 0}
					// {0, 1}

					// {a, b}(x)
					// {c, d}(y)

					// (cos(t)x + -sin(t)y, sin(t)x + cos(t)y)

					//(ax +by, cx+ dy)
					float x = j + offsetX;
					float y = i + offsetY;
					SetPixelV(memdc, x,y, COLOR);
				//cout << maze[i][j] << "";
			//	cout << "\u001b[" << 40 + maze[i][j] << ";" << "1m" << " ";
				//cout << "\033[0m";
			}
			//std::cout << '\n';
		//	cout << "\033[0m";
		}
	}

	void clearBuffer(int Xcoord, int Ycoord, MatrixMxN<float> transform) {

		int offsetX = 0;
		int offsetY = 0;

		float Sx = transform(0, 0);
		float Sy = transform(1, 1);

		if (Sx <= 0)
			Sx = 1;

		if (Sy <= 0)
			Sy = 1;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {

				int sum = img.get_pixel(j, i).red + img.get_pixel(j, i).green + img.get_pixel(j, i).blue;
				if (sum < 765) {
					COLORREF COLOR = RGB(0, 0, 0);
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

	void loadImageBuffer(bitmap_image image) {
		img = image;

		width = img.width();
		height = img.height();
	}

	void displayImage(int resX, int resY) { // Render image to buffer (Screen) with the desired canvas size
		BitBlt(mydc, 0, 0, resX, resY, memdc, 0, 0, SRCCOPY);
	}

private:
	bitmap_image img;
	int width = 0;
	int height = 0;

	HWND myconsole = GetConsoleWindow();
	//Get a handle to device context
	HDC mydc = GetDC(myconsole);
	HDC memdc = CreateCompatibleDC(mydc);
	HBITMAP hbitmap;

	void readImg(const char * filename) {
		img = bitmap_image(filename);

		width = img.width();
		height = img.height();
	}
};

