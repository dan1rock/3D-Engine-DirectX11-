#pragma once
#include "Vector3.h"
#include <memory>

class Matrix {
public:
	Matrix() {

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