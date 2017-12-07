// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"
#include "PartiKillburnLib/Source/Public/Particle/ParticleSystem.h"

// ------------------------------------------------------------

class PartiKillburnEngine
{
public:

	static RandomGeneration randomGenerator;

	PartiKillburnEngine(const ParticleSystem& inSystem, float inUpdateDelta);
	PartiKillburnEngine(const PartiKillburnEngine& that) = delete;

	void SetWindDirection(Vector3 inWindDirection);
	void Update();

protected:

	virtual void UpdateLifetimes() {}
	// if verlet integration comes through for us we won't need this (don't need velocities for positions)
	virtual void UpdateVelocities() {}
	virtual void UpdatePositions() {}
	virtual void SortAlphaBlending() {}
	virtual void TransferTextureData() {}
	virtual void RenderParticles();

	ParticleSystem particleSystem;

	Vector3 windDirection;

	// verlet integration relies on a constant time delta
	const float updateDelta;
};

// ------------------------------------------------------------
