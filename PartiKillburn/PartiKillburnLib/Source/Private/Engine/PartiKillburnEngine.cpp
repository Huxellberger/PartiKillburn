// Jake Huxell (C) 2017

#include "stdafx.h"
#include "PartiKillburnLib/Source/Public/Engine/PartiKillburnEngine.h"

#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"
#include <Dependencies/freeglut/freeglut.h>
#include <time.h>

// ------------------------------------------------------------

PartiKillburnEngine::PartiKillburnEngine(const ParticleSystem& inSystem, float inUpdateDelta)
	: particleSystem(inSystem)
	, windDirection()
	, updateDelta(inUpdateDelta)
{
	PartiKillburnRandomGeneration::randomGenerator.seed((unsigned int) time(nullptr));
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

void PartiKillburnEngine::UpdateLifetimes()
{
	particleSystem.AddParticles(1);
}

// ------------------------------------------------------------

void PartiKillburnEngine::UpdatePositions()
{
	for (ParticleSystemCount currentParticle = 0; currentParticle < particleSystem.GetCurrentActiveParticles(); ++currentParticle)
	{
		particleSystem.particles[currentParticle].UpdatePosition(updateDelta, windDirection);
	}
}

// ------------------------------------------------------------

void PartiKillburnEngine::RenderParticles()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto&& color = particleSystem.GetParticleColor();
	glColor4f(color.r, color.g, color.b, color.a);
	glMatrixMode(GL_MODELVIEW);

	for (ParticleSystemCount currentParticle = 0; currentParticle < particleSystem.GetCurrentActiveParticles(); ++currentParticle)
	{
		glLoadIdentity();
		auto&& particle = particleSystem.particles[currentParticle];
		auto&& position = particle.currentPosition;
		glTranslatef(position.x, position.y, position.z);

		glutSolidSphere(particle.GetSize(), 20, 20);
		glFlush();
	}

	glutSwapBuffers();
}

// ------------------------------------------------------------
