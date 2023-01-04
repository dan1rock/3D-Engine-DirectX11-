#pragma once
#include "Vector3.h"
#include <memory>

class Matrix {
public:
	Matrix() {

	}

	void operator *=(const Matrix matrix) {
		Matrix res;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				res.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
			}
		}
		::memcpy(mat, res.mat, sizeof(float) * 16);
	}

	void setIdentity() {
		::memset(mat, 0, sizeof(float) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setTranslation(const Vector3& vector) {
		setIdentity();
		mat[3][0] = vector.x;
		mat[3][1] = vector.y;
		mat[3][2] = vector.z;
	}

	void setScale(const Vector3& scale) {
		setIdentity();
		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;
	}

	void setRotationX(float x) {
		mat[1][1] = cos(x);
		mat[1][2] = sin(x);
		mat[2][1] = -sin(x);
		mat[2][2] = cos(x);
	}

	void setRotationY(float y) {
		mat[0][0] = cos(y);
		mat[0][2] = -sin(y);
		mat[2][0] = sin(y);
		mat[2][2] = cos(y);
	}

	void setRotationZ(float z) {
		mat[0][0] = cos(z);
		mat[0][1] = sin(z);
		mat[1][0] = -sin(z);
		mat[1][1] = cos(z);
	}

	void setOrthoPM(float width, float height, float nearPlane, float farPlane) {
		setIdentity();
		mat[0][0] = 2.0f / width;
		mat[1][1] = 2.0f / height;
		mat[2][2] = 1.0f / (farPlane - nearPlane);
		mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	~Matrix() {

	}

	float mat[4][4] = {};
};
