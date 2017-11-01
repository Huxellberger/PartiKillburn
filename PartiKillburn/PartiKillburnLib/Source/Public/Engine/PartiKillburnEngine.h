// Jake Huxell (C) 2017

#pragma once

// ------------------------------------------------------------

class PartiKillburnEngine
{
public:

	PartiKillburnEngine(const float inUpdateDelta);
	PartiKillburnEngine(const PartiKillburnEngine& that) = delete;

	void Update();

protected:

	virtual void UpdateLifetimes() {}
	// if verlet integration comes through for us we won't need this (don't need velocities for positions)
	virtual void UpdateVelocities() {}
	virtual void UpdatePositions() {}
	virtual void SortAlphaBlending() {}
	virtual void TransferTextureData() {}
	virtual void RenderParticles();

	// verlet integration relies on a constant time delta
	const float updateDelta;
};

// ------------------------------------------------------------
