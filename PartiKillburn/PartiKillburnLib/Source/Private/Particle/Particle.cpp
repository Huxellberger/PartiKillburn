// Jake Huxell (C) 2017

#include "stdafx.h"
#include "Source/Public/Particle/Particle.h"

// ------------------------------------------------------------

Particle::Particle()
	: Particle(ParticleParams())
{
}

// ------------------------------------------------------------

Particle::Particle(const ParticleParams& inParams)
	: currentPosition(inParams.startPosition)
	, resting(false)
	, size(inParams.size)
	, drift(inParams.drift)
{
}

// ------------------------------------------------------------
