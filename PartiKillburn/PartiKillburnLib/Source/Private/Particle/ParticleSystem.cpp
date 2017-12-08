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
	// currentActiveParticles = 0;
}

// ------------------------------------------------------------

void ParticleSystem::Reset()
{
	currentActiveParticles = 0;
}

// ------------------------------------------------------------

void ParticleSystem::IncreaseCapacity()
{
	delete[params.maxParticles] particles;

	params.maxParticles *= 10;
	particles = new Particle[params.maxParticles];
}

// ------------------------------------------------------------

void ParticleSystem::DecreaseCapacity()
{
	delete[params.maxParticles] particles;

	currentActiveParticles = 0u;

	params.maxParticles *= 0.5;
	particles = new Particle[params.maxParticles];
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

const ParticleSystemCount ParticleSystem::GetCapacity() const
{
	return params.maxParticles;
}

// ------------------------------------------------------------

void ParticleSystem::MaxOutParticles()
{
	AddParticles(params.maxParticles);
}

// ------------------------------------------------------------

void ParticleSystem::GenerateParticle()
{
	const bool drifting = distDrift(PartiKillburnRandomGeneration::randomGenerator) < params.driftPercentage;

	particles[currentActiveParticles] = Particle(ParticleParams(params.bounds.GetRandomPoint(), distSize(PartiKillburnRandomGeneration::randomGenerator), drifting));
}

// ------------------------------------------------------------
