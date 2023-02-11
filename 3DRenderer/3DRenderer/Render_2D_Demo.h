#pragma once
#include "Renderer_2D.h"
void Demo_2D() {
	Renderer_2D img;

	bitmap_image dvd("dvd.bmp");
	bitmap_image disc("disc.bmp");

	img.loadImageBuffer(dvd);

	img.setCanvas(854, 480);

	float theta = 0.0f;
	float prevT = 0.0f;

	float diagonal = 150;

	MatrixMxN<float> transform(4, 4);
	MatrixMxN<float> rotation(4, 4);
	MatrixMxN<float> id(4, 4);
	bool Mode = 0;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	MatrixMxN<int> A(3, 3);
	MatrixMxN<int> B(3, 3);
	A.randomize();
	B.randomize();
	MatrixMxN<int> C(3, 1);

	C.randomize();

	float x = 0;
	float y = 0;

	float prevX = 0;
	float prevY = 0;

	float xM = 400;
	float yM = 400;
	int state = 0;

	for (; ;) {
		// Standard matrix with basis = (1,0), (0,1)
		img.loadImageBuffer(dvd);

		if (x > xM && y > yM && state == 0)
			state = 1;

		if (x < 0 && y < 0 && state == 1)
			state = 0;

		if (state == 0) {
			prevX = x;
			prevY = y;
			x++;
			y++;
		}
		else {
			prevX = x;
			prevY = y;
			x--;
			y--;
		}

		prevT = theta;
		theta -= 0.5f;

		rotation.RotateZ(prevT);
		rotation.res_to_matrix();

		transform.Translate3D(prevX, prevY, 0);
		transform.res_to_matrix();
		transform.matmul(rotation);
		transform.res_to_matrix();

		//img.deleteImage();
		//img.setCanvas(854, 480);
	//	transform.Rotate(theta);
	//	transform.res_to_matrix();
		img.clearBuffer(diagonal, diagonal, transform);


		if ((int)diagonal <= 150)
			Mode = 0;

		if (diagonal > 350)
			Mode = 1;

		if (Mode == 0)
			diagonal += 1;
		else
			diagonal -= 1;

		transform.Translate3D(x, y, 0);
		transform.res_to_matrix();
		rotation.RotateZ(theta);
		rotation.res_to_matrix();

		transform.matmul(rotation);
		transform.res_to_matrix();

		img.renderImage(diagonal, diagonal, transform);

		id.Translate3D(420, 427, 0);
		id.res_to_matrix();

		img.loadImageBuffer(disc);
		img.renderImage(320, 427, id);

		img.displayImage(854, 480);
	}

}