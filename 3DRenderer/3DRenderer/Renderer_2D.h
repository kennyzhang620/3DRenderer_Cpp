#pragma once
#pragma warning(disable : 4996)

#include <cstdio>
#include <iostream>
#include <vector>
#include "Bitmap.h"
#include "Backtracker.h"
#include <Windows.h>
#include "MatrixMxN.h"
#include <math.h>

using namespace std;

// Old class created in 2020 to support basic 2D rendering with transforms.
// Used to help study for linear algebra.
// Image data is stored as part of this class.

// 3D class supports 2D rasterization and many more effects, but you must pass pointers to image data and others outside of it.
class Renderer_2D
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

	void readImg(const char* filename) {
		img = bitmap_image(filename);

		width = img.width();
		height = img.height();
	}
};

