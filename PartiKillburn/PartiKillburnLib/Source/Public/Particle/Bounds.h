// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"
#include "PartiKillburnLib/Source/Public/Particle/Vector3.h"

#include <random>

// ------------------------------------------------------------

struct Bounds
{
public:

	Bounds()
		: Bounds(Vector3(), Vector3())
	{
	}

	Bounds(const Vector3& inStartExtent, const Vector3& inEndExtent)
		: startExtent(inStartExtent)
		, endExtent(inEndExtent)
		, realXDist(startExtent.x, endExtent.x)
		, realYDist(startExtent.y, endExtent.y)
		, realZDist(startExtent.z, endExtent.z)
	{
	}

	Vector3 GetRandomPoint() const
	{
		return Vector3
		(
			realXDist(PartiKillburnRandomGeneration::randomGenerator), 
			realYDist(PartiKillburnRandomGeneration::randomGenerator), 
			realZDist(PartiKillburnRandomGeneration::randomGenerator)
		);
	}

private:

	const Vector3 startExtent;
	const Vector3 endExtent;

	std::uniform_real_distribution<float> realXDist;
	std::uniform_real_distribution<float> realYDist;
	std::uniform_real_distribution<float> realZDist;
};

// ------------------------------------------------------------
