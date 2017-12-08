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
	: particles()
	, distSize(inParams.minSize, inParams.maxSize)
	, distDrift(0.0f, 1.0f)
	, params(inParams)
	, currentActiveParticles(0u)
{
	particles.reserve(params.maxParticles);
}

// ------------------------------------------------------------

ParticleSystem::~ParticleSystem()
{
	particles.empty();
}

// ------------------------------------------------------------

void ParticleSystem::Reset()
{
	currentActiveParticles = 0;
}

// ------------------------------------------------------------

void ParticleSystem::IncreaseCapacity()
{
	params.maxParticles *= 10;
	particles.reserve(params.maxParticles);
}

// ------------------------------------------------------------

void ParticleSystem::DecreaseCapacity()
{
	params.maxParticles *= 0.5;

	if (currentActiveParticles > params.maxParticles)
	{
		currentActiveParticles = params.maxParticles;
	}
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

void ParticleSystem::GenerateParticle()
{
	const bool drifting = distDrift(PartiKillburnRandomGeneration::randomGenerator) < params.driftPercentage;

	particles.push_back(Particle(ParticleParams(params.bounds.GetRandomPoint(), distSize(PartiKillburnRandomGeneration::randomGenerator), drifting)));
}

// ------------------------------------------------------------
