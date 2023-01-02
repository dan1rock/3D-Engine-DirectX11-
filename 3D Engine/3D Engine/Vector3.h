#pragma once

class Vector3 
{
public:
	Vector3(): x(0), y(0), z(0)
	{

	}

	Vector3(float coordX, float coordY, float coordZ) : x(coordX), y(coordY), z(coordZ) {

	}

	Vector3(const Vector3& vector) : x(vector.x), y(vector.y), z(vector.z) {

	}

	float x, y, z;
};