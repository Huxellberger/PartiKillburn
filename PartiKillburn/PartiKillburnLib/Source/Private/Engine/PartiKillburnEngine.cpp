// Jake Huxell (C) 2017

#include "stdafx.h"
#include "Source/Public/Engine/PartiKillburnEngine.h"
#include <Dependencies/freeglut/freeglut.h>

// ------------------------------------------------------------

PartiKillburnEngine::PartiKillburnEngine(const ParticleSystem& inSystem, float inUpdateDelta)
	: particleSystem(inSystem)
	, updateDelta(inUpdateDelta)
{
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
