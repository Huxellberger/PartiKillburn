// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Collidable/CollidableInterface.h"
#include "PartiKillburnLib/Source/Public/Engine/PartiKillburnEngineConstants.h"
#include "PartiKillburnLib/Source/Public/Particle/Vector3.h"

#include <Dependencies/freeglut/freeglut.h>

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
	: public CollidableInterface
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

	// CollidableInterface
	virtual inline bool HasCollided(const Vector3& inPoint) const override final
	{
		if (resting)
		{
			return true;
		}

		const Vector3 distanceApart = currentPosition - inPoint;

		const float magnitueSquared = (distanceApart.x * distanceApart.x) + (distanceApart.y * distanceApart.y) + (distanceApart.z *distanceApart.z);

		return magnitueSquared < (size * size);
	}

	virtual inline void DrawCollidable(const ParticleColor& inColor) override final
	{
		// trail
		if (!resting)
		{
			// Trail transparency
			glColor4f(inColor.r, inColor.g, inColor.b, inColor.a * 0.2f);

			auto&& trailStartPosition = currentPosition - ((currentPosition - startPosition).Scale(0.1f));

			const float particleOffset = size;
			const float halfOffset = particleOffset * 0.5f;

			glBegin(GL_POLYGON);
			glVertex3f(trailStartPosition.x, trailStartPosition.y, trailStartPosition.z);
			glVertex3f(currentPosition.x + halfOffset, currentPosition.y + particleOffset, currentPosition.z + halfOffset);
			glVertex3f(currentPosition.x - halfOffset, currentPosition.y + particleOffset, currentPosition.z - halfOffset);
			glEnd();
		}
		// splat
		else
		{
			// Splat code
		}

		// normal particle

		// Solid Snow
		glColor4f(inColor.r, inColor.g, inColor.b, inColor.a);

		glPushMatrix();
		glTranslatef(currentPosition.x, currentPosition.y, currentPosition.z);
		glutSolidSphere(size, 20, 20);
		glPopMatrix();
	}
	// ~CollidableInterface

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
