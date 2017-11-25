// Jake Huxell (C) 2017

#pragma once

#include "Source/Public/Particle/Vector3.h"

// ------------------------------------------------------------

class _declspec(dllexport) Particle
{
public:

	Particle(const Vector3& inStartPos, float inSize, bool inDrift);

	inline const bool CanDrift() const;
	inline const float GetSize() const;

	Vector3 currentPosition;
	bool resting;

private:

	float size;
	bool drift;
};

// ------------------------------------------------------------
