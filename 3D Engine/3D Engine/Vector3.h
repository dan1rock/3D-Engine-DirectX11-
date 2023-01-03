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

	static Vector3 lerp(const Vector3& startPos, const Vector3 endPos, float delta) {
		Vector3 res;
		res.x = startPos.x * (1.0f - delta) + endPos.x * delta;
		res.y = startPos.y * (1.0f - delta) + endPos.y * delta;
		res.z = startPos.z * (1.0f - delta) + endPos.z * delta;
		return res;
	}

	float x, y, z;
};