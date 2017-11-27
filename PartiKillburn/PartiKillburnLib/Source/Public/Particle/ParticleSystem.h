// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Particle/Particle.h"

#include <basetsd.h>
#include <vector>

using ParticleSystemCount = UINT32;

// ------------------------------------------------------------

class ParticleSystem
{
public:

	ParticleSystem();
	ParticleSystem(const std::vector<ParticleParams>& inParamTypes, ParticleSystemCount inCount);

	void Update();
	const ParticleSystemCount GetCurrentActiveParticles() const;

	Particle* particles;

private:
	std::vector<ParticleParams> paramTypes;
	
	ParticleSystemCount maxParticles;
	ParticleSystemCount currentType;
	ParticleSystemCount currentActiveParticles;
};

// ------------------------------------------------------------
