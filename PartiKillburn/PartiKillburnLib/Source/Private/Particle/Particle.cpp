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
	, splatDeviation(inParams.size, inParams.size * 3.0f)
	, startPosition(inParams.startPosition)
	, priorPosition(inParams.startPosition)
	, size(inParams.size)
	, lifetime(0.0f)
	, splatXOffset(splatDeviation(PartiKillburnRandomGeneration::randomGenerator))
	, splatZOffset(splatDeviation(PartiKillburnRandomGeneration::randomGenerator))
	, drift(inParams.drift)
{
}

// ------------------------------------------------------------
