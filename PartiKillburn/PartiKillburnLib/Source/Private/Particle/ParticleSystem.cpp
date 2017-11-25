// Jake Huxell (C) 2017

#include "stdafx.h"
#include "Source/Public/Particle/ParticleSystem.h"

#include <CRTDBG.H>

// ------------------------------------------------------------

ParticleSystem::ParticleSystem(const std::vector<ParticleParams>& inParamTypes, ParticleSystemCount inCount)
	: particles(new Particle[inCount])
	, paramTypes(inParamTypes)
	, maxParticles(inCount)
	, currentType(0)
	, currentActiveParticles(0u)
{
	_ASSERT(paramTypes.size() != 0);
}

// ------------------------------------------------------------

void ParticleSystem::Update()
{
	if (currentActiveParticles < maxParticles)
	{
		if (currentType >= paramTypes.size())
		{
			currentType = 0;
		}

		particles[currentActiveParticles] = Particle(paramTypes[currentType]);
		currentActiveParticles++;
		currentType++;
	}
}

// ------------------------------------------------------------

const ParticleSystemCount ParticleSystem::GetCurrentActiveParticles() const
{
	return currentActiveParticles;
}

// ------------------------------------------------------------
