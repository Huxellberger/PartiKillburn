// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Collidable/CollidableInterface.h"
#include "PartiKillburnLib/Source/Public/Particle/ParticleSystem.h"
#include "PartiKillburnLib/Source/Public/Particle/Vector3.h"

#include <random>
#include <vector>

// ------------------------------------------------------------

class PartiKillburnEngine
{
public:

	const static float MOVE_SPEED;

	PartiKillburnEngine(const ParticleSystem& inSystem, const float inUpdateDeltaSeconds, const float inGroundYPosition, const std::vector<CollidableInterface*>& inCollidables);
	PartiKillburnEngine(const PartiKillburnEngine& that) = delete;

	void Initialise();
	void OnMenuSelected(int selection);
	void OnKeyboardSelection(unsigned char key, int x, int y);
	void SetWindDirection(Vector3 inWindDirection);
	void Update();
	void Resize(int w, int h);

protected:

	virtual void UpdateLifetimes();
	virtual void UpdatePositions();
	virtual void RenderParticles();

	void CreateMenu();
	void SetView();

	std::vector<CollidableInterface*> collidables;

	ParticleSystem particleSystem;
	Particle sun;

	Vector3 currentPosition;
	Vector3 windDirection;

	std::uniform_real_distribution<float> windDist;

	// verlet integration relies on a constant time delta
	const float updateDeltaSeconds;

	const float groundYPosition;
};

// ------------------------------------------------------------
