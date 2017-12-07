// Jake Huxell (C) 2017

#include "stdafx.h"
#include "Source/Public/Engine/PartiKillburnEngine.h"
#include <Dependencies/freeglut/freeglut.h>
#include <time.h>

// ------------------------------------------------------------

RandomGeneration PartiKillburnEngine::randomGenerator = RandomGeneration((unsigned int)time(nullptr));

// ------------------------------------------------------------

PartiKillburnEngine::PartiKillburnEngine(const ParticleSystem& inSystem, float inUpdateDelta)
	: particleSystem(inSystem)
	, windDirection()
	, updateDelta(inUpdateDelta)
{
	randomGenerator.seed((unsigned int) time(nullptr));
}

// ------------------------------------------------------------

// Magnitude of said vector determines the strength.
void PartiKillburnEngine::SetWindDirection(Vector3 inWindDirection)
{
	windDirection = inWindDirection;
}

// ------------------------------------------------------------

void PartiKillburnEngine::Update()
{
	UpdateLifetimes();
	UpdateVelocities();
	UpdatePositions();
	SortAlphaBlending();
	TransferTextureData();
	RenderParticles();
}

// ------------------------------------------------------------

void PartiKillburnEngine::RenderParticles()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	glutSwapBuffers();
}

// ------------------------------------------------------------
