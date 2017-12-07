// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Particle/ParticleSystem.h"
#include "PartiKillburnLib/Source/Public/Particle/Vector3.h"

// ------------------------------------------------------------

class PartiKillburnEngine
{
public:

	PartiKillburnEngine(const ParticleSystem& inSystem, const float inUpdateDeltaSeconds, const float inGroundYPosition);
	PartiKillburnEngine(const PartiKillburnEngine& that) = delete;

	void Initialise();
	void SetWindDirection(Vector3 inWindDirection);
	void Update();
	void Resize(int w, int h);

protected:

	virtual void UpdateLifetimes();
	// if verlet integration comes through for us we won't need this (don't need velocities for positions)
	virtual void UpdateVelocities() {}
	virtual void UpdatePositions();
	virtual void SortAlphaBlending() {}
	virtual void TransferTextureData() {}
	virtual void RenderParticles();

	void SetView();

	ParticleSystem particleSystem;

	Vector3 windDirection;

	// verlet integration relies on a constant time delta
	const float updateDeltaSeconds;

	const float groundYPosition;
};

// ------------------------------------------------------------
