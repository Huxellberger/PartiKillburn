// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Particle/Vector3.h"

// ------------------------------------------------------------

struct ParticleParams
{
public:

	ParticleParams()
		: startPosition(Vector3())
		, size(0.f)
		, drift(true)
	{
	}

	explicit ParticleParams(const Vector3& inStartPos, float inSize, bool inDrift)
		: startPosition(inStartPos)
		, size(inSize)
		, drift(inDrift)
	{
	}

	Vector3 startPosition;
	float size;
	bool drift;
};

// ------------------------------------------------------------

class Particle
{
public:

	Particle();
	explicit Particle(const ParticleParams& inParams);

	inline const bool CanDrift() const
	{
		return drift;
	}

	inline const float GetSize() const
	{
		return size;
	}

	Vector3 currentPosition;
	bool resting;

private:

	float size;
	bool drift;
};

// ------------------------------------------------------------
