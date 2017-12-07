// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Engine/PartiKillburnEngine.h"
#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"
#include "PartiKillburnLib/Source/Public/Particle/Vector3.h"

#include <random>

// ------------------------------------------------------------

struct Bounds
{
public:

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
		return Vector3(realXDist(PartiKillburnEngine::randomGenerator), realYDist(PartiKillburnEngine::randomGenerator), realZDist(PartiKillburnEngine::randomGenerator));
	}

private:

	const Vector3 startExtent;
	const Vector3 endExtent;

	std::uniform_real_distribution<float> realXDist;
	std::uniform_real_distribution<float> realYDist;
	std::uniform_real_distribution<float> realZDist;
};

// ------------------------------------------------------------