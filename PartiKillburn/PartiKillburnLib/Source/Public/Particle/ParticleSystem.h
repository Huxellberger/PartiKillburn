// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Particle/Bounds.h"
#include "PartiKillburnLib/Source/Public/Particle/Particle.h"
#include "PartiKillburnLib/Source/Public/Particle/ParticleColor.h"

#include <basetsd.h>
#include <random>
#include <vector>

// ------------------------------------------------------------

using ParticleSystemCount = UINT32;

// ------------------------------------------------------------

struct ParticleSystemParams
{
	ParticleSystemParams()
		: ParticleSystemParams(Bounds(), ParticleColor(), 0.0f, 0.0f, 0.0f, 0u)
	{
	}

	ParticleSystemParams
	(
		const Bounds& inBounds,
		const ParticleColor& inColor,
		const float inMinSize,
		const float inMaxSize,
		const float inDriftPercentage,
		const ParticleSystemCount inMaxParticles
	)
		: bounds(inBounds)
		, color(inColor)
		, minSize(inMinSize)
		, maxSize(inMaxSize)
		, driftPercentage(inDriftPercentage)
		, maxParticles(inMaxParticles)
	{
	}

	Bounds bounds;
	ParticleColor color;

	float minSize;
	float maxSize;
	float driftPercentage;

	ParticleSystemCount maxParticles;
};

// ------------------------------------------------------------

class ParticleSystem
{
public:

	ParticleSystem();
	ParticleSystem(const ParticleSystemParams& inSystemParams);

	virtual ~ParticleSystem();

	void Reset();
	void AddParticles(ParticleSystemCount numberToAdd);
	void IncreaseCapacity();
	void DecreaseCapacity();
	void MaxOutParticles();
	const ParticleSystemCount GetCurrentActiveParticles() const;
	const ParticleColor GetParticleColor() const;
	const ParticleSystemCount GetCapacity() const;

	Particle* particles;

private:

	void GenerateParticle();

	std::uniform_real_distribution<float> distSize;
	std::uniform_real_distribution<float> distDrift;

	ParticleSystemParams params;
	
	ParticleSystemCount currentActiveParticles;
};

// ------------------------------------------------------------
