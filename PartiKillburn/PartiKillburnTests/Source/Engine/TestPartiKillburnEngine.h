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

	TestPartiKillburnEngine(const ParticleSystem& inSystem, const float inTimeDelta)
		: PartiKillburnEngine(inSystem, inTimeDelta, 1.0f, std::vector <CollidableInterface*>() )
		, updateLifetimesCalled(false)
		, updateVelocitiesCalled(false)
		, updatePositionsCalled(false)
		, sortAlphaBlendingCalled(false)
		, transferTextureDataCalled(false)
		, renderParticlesCalled(false)
	{
	}

	const float GetTimeDelta() const
	{
		return updateDeltaSeconds;
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
	bool updateVelocitiesCalled;
	bool updatePositionsCalled;
	bool sortAlphaBlendingCalled;
	bool transferTextureDataCalled;
	bool renderParticlesCalled;

private:

	virtual void UpdateLifetimes() override final { updateLifetimesCalled = true; }
	virtual void UpdateVelocities() override final { updateVelocitiesCalled = true; }
	virtual void UpdatePositions() override final { updatePositionsCalled = true; }
	virtual void SortAlphaBlending() override final { sortAlphaBlendingCalled = true; }
	virtual void TransferTextureData() override final { transferTextureDataCalled = true; }
	virtual void RenderParticles() override final { renderParticlesCalled = true; }
};

// ------------------------------------------------------------
