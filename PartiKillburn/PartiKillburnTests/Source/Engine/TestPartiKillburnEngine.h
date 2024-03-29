// Jake Huxell (C) 2017

#pragma once

#include "Source/Public/Engine/PartiKillburnEngine.h"
#include "Source/Public/Particle/Particle.h"
#include "Source/Public/Particle/ParticleSystem.h"

#include <vector>

// ------------------------------------------------------------

class TestPartiKillburnEngine
	: public PartiKillburnEngine
{
public:

	TestPartiKillburnEngine(const ParticleSystem& inSystem)
		: PartiKillburnEngine(inSystem, 1.0f, std::vector <CollidableInterface*>() )
		, updateLifetimesCalled(false)
		, updatePositionsCalled(false)
		, renderParticlesCalled(false)
	{
	}

	const Vector3 GetWindDirection() const
	{
		return windDirection;
	}

	const ParticleSystem GetParticleSystem() const
	{
		return particleSystem;
	}

	bool updateLifetimesCalled;
	bool updatePositionsCalled;
	bool renderParticlesCalled;

private:

	virtual void UpdateLifetimes() override final { updateLifetimesCalled = true; }
	virtual void UpdatePositions(const float inDelta) override final { updatePositionsCalled = true; }
	virtual void RenderParticles() override final { renderParticlesCalled = true; }
};

// ------------------------------------------------------------
