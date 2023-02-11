#pragma once
#include <iostream>
#include <vector>
#include "VectorCoords.h"

using namespace std;

template <typename T>
class MatrixMxN
{
private:
	
public:
	vector<vector<T>> matrix; // Initializes with the identity matrix
	vector<vector<T>> matrixres; // Resultant matrix
	int sizeM = 0;
	int sizeN = 0;
	
	float& operator() (int i, int j){
		return matrix[i][j];
	}

	MatrixMxN(int M, int N) {
		sizeM = M;
		sizeN = N;
		for (int cols = 0; cols < M; cols++) {
			vector<T> temp;
			for (int rows = 0; rows < N; rows++) {
				if (rows == cols)
					temp.push_back(1);
				else
					temp.push_back(0);
			}
			matrix.push_back(temp);
		}

		for (int cols = 0; cols < M; cols++) {
			vector<T> temp;
			for (int rows = 0; rows < N; rows++) {
				if (rows == cols)
					temp.push_back(1);
				else
					temp.push_back(0);
			}
			matrixres.push_back(temp);
		}
	}

	void randomize() {
		for (int cols = 0; cols < sizeM; cols++) {
			for (int rows = 0; rows < sizeN; rows++) {
				if (rows != cols)
					matrix[cols][rows] = rand() % 50;

			}
		}
	}

	MatrixMxN(int size) {
		MatrixMxN(size, size);
	}

	void Rotate(float angle) { // 2d only

		float rads = (angle * (3.14159)) / 180.0;
		vector<vector<T>> tempRot = { {cos(rads), -sin(rads)},
									  {sin(rads), cos(rads)}};

		std::copy(tempRot.begin(), tempRot.end(),matrixres.begin());
	}

	void Scale(float scaleX, float scaleY) {
		vector<vector<T>> tempRot = { {scaleX, 0},
									  {0, scaleY} };

		std::copy(tempRot.begin(), tempRot.end(),matrixres.begin());
	}


	void Scale3D(float x, float y, float z) {
		matrixres[0][0] = x;
		matrixres[0][1] = 0;
		matrixres[0][2] = 0; matrixres[0][3] = 0;

		matrixres[1][0] = 0; matrixres[1][1] = y;
		matrixres[1][2] = 0; matrixres[1][3] = 0;
		matrixres[2][0] = 0; matrixres[2][1] = 0; matrixres[2][2] = z; matrixres[2][3] = 0;
		matrixres[3][0] = 0; matrixres[3][1] = 0; matrixres[3][2] = 0; matrixres[3][3] = 1;
	}
	
	void Translate3D(float x, float y, float z) {

		matrixres[0][0] = 1; matrixres[0][1] = 0; matrixres[0][2] = 0; matrixres[0][3] = x;
		matrixres[1][0] = 0; matrixres[1][1] = 1; matrixres[1][2] = 0; matrixres[1][3] = y;
		matrixres[2][0] = 0; matrixres[2][1] = 0; matrixres[2][2] = 1; matrixres[2][3] = z;
		matrixres[3][0] = 0; matrixres[3][1] = 0; matrixres[3][2] = 0; matrixres[3][3] = 1;
	}

	void RotateZ(float angle) {
		float rads = (angle * (3.14159)) / 180.0;
		matrixres[0][0] = cos(rads); matrixres[0][1] = -sin(rads); matrixres[0][2] = 0; matrixres[0][3] = 0;
		matrixres[1][0] = sin(rads); matrixres[1][1] = cos(rads); matrixres[1][2] = 0; matrixres[1][3] = 0;
		matrixres[2][0] = 0; matrixres[2][1] = 0; matrixres[2][2] = 1; matrixres[2][3] = 0;
		matrixres[3][0] = 0; matrixres[3][1] = 0; matrixres[3][2] = 0; matrixres[3][3] = 1;
	}

	void RotateY(float angle) {
		float rads = (angle * (3.14159)) / 180.0;
		matrixres[0][0] = cos(rads); matrixres[0][1] = 0; matrixres[0][2] = sin(rads); matrixres[0][3] = 0;
		matrixres[1][0] = 0; matrixres[1][1] = 1; matrixres[1][2] = 0; matrixres[1][3] = 0;
		matrixres[2][0] = -sin(rads); matrixres[2][1] = 0; matrixres[2][2] = cos(rads); matrixres[2][3] = 0;
		matrixres[3][0] = 0; matrixres[3][1] = 0; matrixres[3][2] = 0; matrixres[3][3] = 1;
	}

	void RotateX(float angle) {
		float rads = (angle * (3.14159)) / 180.0;
		matrixres[0][0] = 1; matrixres[0][1] = 0; matrixres[0][2] = 0; matrixres[0][3] = 0;
		matrixres[1][0] = 0; matrixres[1][1] = cos(rads); matrixres[1][2] = -sin(rads); matrixres[1][3] = 0;
		matrixres[2][0] = 0; matrixres[2][1] = sin(rads); matrixres[2][2] = cos(rads); matrixres[2][3] = 0;
		matrixres[3][0] = 0; matrixres[3][1] = 0; matrixres[3][2] = 0; matrixres[3][3] = 1;
		vector<vector<T>> tempRot = { {1, 0,0,0},
									  {0, cos(rads),-sin(rads),0},
									  {0, sin(rads),cos(rads),0},
									  {0, 0,0,1} };

		std::copy(tempRot.begin(), tempRot.end(),matrixres.begin());
	}

	VectorCoords GetTransform(VectorCoords vector) {

	}

	void res_to_matrix() { // Move results from calculation/instantiation into working space.
		std::copy(matrixres.begin(), matrixres.end(), matrix.begin());
	}

	void matmul(MatrixMxN<T> mat2) { // Multiply two matrices using standard matrix multiplcation
		int xN = 0;
		int yN = 0;
		if (sizeN == mat2.sizeM) {
			for (int i = 0; i < sizeM; i++) {
				for (int j = 0; j < mat2.sizeN; j++) {
					float val = 0;
					for (int l = 0; l < sizeN; l++) {
					//	cout << i << l << l << j << "VAL: " << matrix[i][l] << " x " << mat2.matrix[l][j] << "==" << matrix[i][l] * mat2.matrix[l][j] << '\n';
						val += matrix[i][l] * mat2.matrix[l][j];
					}
				//	cout << "Res: " << val << '\n';
					//cout << "  \n";
					matrixres[xN][yN] = val;
					yN++;
				}
				xN++;
				yN = 0;
			}
		}
	}

	VectorCoords matmul_vtr(VectorCoords mat2) { // Multiply 4x1 vector by transformation matrix. Only work with 4x4 matrices and vectors (VectorCoords are 1x4)
		VectorCoords resV;
		float temp[4] = { mat2.x, mat2.y, mat2.z, mat2.w };
		float res[4]; int ind = 0;
		if (sizeN == 4) {
			for (int i = 0; i < sizeM; i++) {
					float val = 0;
					for (int l = 0; l < sizeN; l++) {
						//cout << i << "  " << l << '\n';
						//cout << matrix[i][l] << 'x' << temp[l] << "+" << '\n';
						val += matrix[i][l] * temp[l];
					}
					//cout << "Res: " << val << '\n';
					res[ind++] = val;
			}


			resV.x = res[0]; resV.y = res[1]; resV.z = res[2]; resV.w = res[3]; resV.r = mat2.r; resV.g = mat2.g; resV.b = mat2.b; resV.a = mat2.a;
			return resV;

		}
		else {
			return mat2;
		}

		
	}

};


