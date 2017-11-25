// Jake Huxell (C) 2017

#include "stdafx.h"
#include "Source/Public/Particle/Particle.h"

// ------------------------------------------------------------

Particle::Particle(const Vector3& inStartPos, float inSize, bool inDrift)
	: currentPosition(inStartPos)
	, resting(false)
	, size(inSize)
	, drift(inDrift)
{
}

// ------------------------------------------------------------

inline const bool Particle::CanDrift() const
{
	return drift;
}

// ------------------------------------------------------------

inline const float Particle::GetSize() const
{
	return size;
}

// ------------------------------------------------------------
