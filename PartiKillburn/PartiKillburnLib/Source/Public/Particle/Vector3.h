// Jake Huxell (C) 2017

#pragma once

#include <string>

// ------------------------------------------------------------

struct Vector3
{
public:
	Vector3()
		: x(0.f)
		, y(0.f)
		, z(0.f)
	{
	}

	Vector3(float inX, float inY, float inZ)
		: x(inX)
		, y(inY)
		, z(inZ)
	{
	}

	inline bool operator==(const Vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	inline bool operator!=(const Vector3& other) const
	{
		return !(*this == other);
	}

	float x;
	float y;
	float z;
};

// ------------------------------------------------------------
