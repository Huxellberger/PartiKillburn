// Jake Huxell (C) 2017

#include "stdafx.h"
#include "PartiKillburnLib/Source/Public/Engine/PartiKillburnEngine.h"

#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"
#include <Dependencies/freeglut/freeglut.h>
#include <time.h>

// ------------------------------------------------------------

PartiKillburnEngine::PartiKillburnEngine(const ParticleSystem& inSystem, const float inUpdateDeltaSeconds, const float inGroundYPosition, const std::vector<CollidableInterface*>& inCollidables)
	: collidables(inCollidables)
	, particleSystem(inSystem)
	, windDirection()
	, updateDeltaSeconds(inUpdateDeltaSeconds)
	, groundYPosition(inGroundYPosition)
{
	PartiKillburnRandomGeneration::randomGenerator.seed((unsigned int) time(nullptr));
}

// ------------------------------------------------------------

void PartiKillburnEngine::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

void PartiKillburnEngine::Resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
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
		if (!particleSystem.particles[currentParticle].resting)
		{
			particleSystem.particles[currentParticle].UpdatePosition(updateDeltaSeconds, windDirection);

			if (particleSystem.particles[currentParticle].currentPosition.y <= groundYPosition)
			{
				particleSystem.particles[currentParticle].resting = true;
			}

			for each (auto&& collidable in collidables)
			{
				if (collidable->HasCollided(particleSystem.particles[currentParticle].currentPosition))
				{
					particleSystem.particles[currentParticle].resting = true;
				}
			}
		}
	}
}

// ------------------------------------------------------------

void PartiKillburnEngine::RenderParticles()
{
	SetView();
	glDisable(GL_LIGHTING);

	auto&& color = particleSystem.GetParticleColor();
	auto&& collidableColor = ParticleColor(1.0f, 0.0f, 0.0f, 1.0f);
	auto&& groundColor = ParticleColor(0.0f, 1.0f, 0.0f, 1.0f);

	// Particles
	for (ParticleSystemCount currentParticle = 0; currentParticle < particleSystem.GetCurrentActiveParticles(); ++currentParticle)
	{
		particleSystem.particles[currentParticle].DrawCollidable(color);
	}

	// Collidables
	for (std::vector<CollidableInterface*>::iterator it = collidables.begin(); it != collidables.end(); ++it)
	{
		(*it)->DrawCollidable(collidableColor);
	}

	// Ground
	glColor4f(groundColor.r, groundColor.g, groundColor.b, groundColor.a);

	glBegin(GL_POLYGON);
	glVertex3f(-1000.0f, groundYPosition, -1000.0f);
	glVertex3f(1000.0f, groundYPosition, -1000.0f);
	glVertex3f(-1000.0f, groundYPosition, 1000.0f);
	glVertex3f(1000.0f, groundYPosition, 1000.0f);
	glEnd();

	glutSwapBuffers();
}

// ------------------------------------------------------------

void PartiKillburnEngine::SetView()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0, 40, 0.0, -10.0, 0.0, 0.0, 1.0, 0.0);
}

// ------------------------------------------------------------
