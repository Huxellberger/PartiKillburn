// Jake Huxell (C) 2017

#include "stdafx.h"
#include "PartiKillburnLib/Source/Public/Particle/ParticleSystem.h"

#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"

// ------------------------------------------------------------

ParticleSystem::ParticleSystem()
	: ParticleSystem(ParticleSystemParams())
{
}

// ------------------------------------------------------------

ParticleSystem::ParticleSystem(const ParticleSystemParams& inParams)
	: particles(new Particle[inParams.maxParticles])
	, distSize(inParams.minSize, inParams.maxSize)
	, distDrift(0.0f, 1.0f)
	, params(inParams)
	, currentActiveParticles(0u)
{
}

// ------------------------------------------------------------

ParticleSystem::~ParticleSystem()
{
	// delete[params.maxParticles] particles;
}

// ------------------------------------------------------------

void ParticleSystem::AddParticles(ParticleSystemCount numberToAdd)
{
	for (ParticleSystemCount currentAddition = 0; currentAddition < numberToAdd; ++currentAddition)
	{
		if (currentActiveParticles < params.maxParticles)
		{
			GenerateParticle();
			currentActiveParticles++;
		}
	}
}

// ------------------------------------------------------------

const ParticleSystemCount ParticleSystem::GetCurrentActiveParticles() const
{
	return currentActiveParticles;
}

// ------------------------------------------------------------

const ParticleColor ParticleSystem::GetParticleColor() const
{
	return params.color;
}

// ------------------------------------------------------------

void ParticleSystem::GenerateParticle()
{
	const bool drifting = distDrift(PartiKillburnRandomGeneration::randomGenerator) < params.driftPercentage;

	particles[currentActiveParticles] = Particle(ParticleParams(params.bounds.GetRandomPoint(), distSize(PartiKillburnRandomGeneration::randomGenerator), drifting));
}

// ------------------------------------------------------------
