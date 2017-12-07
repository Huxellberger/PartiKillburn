// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Engine/PartiKillburnEngineConstants.h"
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

	inline void UpdatePosition(const float inDelta, const Vector3& inWind)
	{
		lifetime += inDelta;
		if (!resting)
		{
			float timeDeltaSquared = inDelta * inDelta;

			float accX = drift ? inWind.x : 0;
			float newPositionX = (2 * currentPosition.x - priorPosition.x) + ((accX * 1.0f / size) * timeDeltaSquared);

			float accY = PartiKillburnEngineConstants::GRAVITY;
			float newPositionY = (2 * currentPosition.y - priorPosition.y) + (accY * timeDeltaSquared);

			float accZ = drift ? inWind.z : 0;
			float newPositionZ = (2 * currentPosition.z - priorPosition.z) + ((accZ * 1.0f / size) * timeDeltaSquared);

			priorPosition = currentPosition;
			currentPosition = Vector3(newPositionX, newPositionY, newPositionZ);
		}
	}

	inline const bool CanDrift() const
	{
		return drift;
	}

	inline const float GetSize() const
	{
		return size;
	}

	inline const Vector3 GetStartPosition() const
	{
		return startPosition;
	}

	inline const Vector3 GetPriorPosition() const
	{
		return priorPosition;
	}

	Vector3 currentPosition;
	bool resting;

private:

	Vector3 startPosition;
	Vector3 priorPosition;
	float size;
	float lifetime;
	bool drift;
};

// ------------------------------------------------------------
