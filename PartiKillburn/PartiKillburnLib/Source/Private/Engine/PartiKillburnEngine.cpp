// Jake Huxell (C) 2017

#include "stdafx.h"
#include "PartiKillburnLib/Source/Public/Engine/PartiKillburnEngine.h"

#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"
#include <Dependencies/freeglut/freeglut.h>
#include <time.h>

// ------------------------------------------------------------

PartiKillburnEngine::PartiKillburnEngine(const ParticleSystem& inSystem, const float inUpdateDeltaSeconds, const float inGroundYPosition)
	: particleSystem(inSystem)
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
		}
	}
}

// ------------------------------------------------------------

void PartiKillburnEngine::RenderParticles()
{
	SetView();
	glDisable(GL_LIGHTING);

	auto&& color = particleSystem.GetParticleColor();

	for (ParticleSystemCount currentParticle = 0; currentParticle < particleSystem.GetCurrentActiveParticles(); ++currentParticle)
	{
		auto&& particle = particleSystem.particles[currentParticle];
		auto&& currentPosition = particle.currentPosition;

		// Trails
		glColor4f(color.r, color.g, color.b, color.a * 0.2f);

		if (!particleSystem.particles[currentParticle].resting)
		{
			auto&& startPosition = particle.GetStartPosition();
			auto&& trailStartPosition = currentPosition - ((currentPosition - particle.GetStartPosition()).Scale(0.1f));
			float particleOffset = particle.GetSize();
			float halfOffset = particleOffset * 0.5f;

			glBegin(GL_POLYGON);
			glVertex3f(trailStartPosition.x, trailStartPosition.y, trailStartPosition.z);
			glVertex3f(currentPosition.x + halfOffset, currentPosition.y + particleOffset, currentPosition.z + halfOffset);
			glVertex3f(currentPosition.x - halfOffset, currentPosition.y + particleOffset, currentPosition.z - halfOffset);
			glEnd();
		}

		// Solid Snow
		glColor4f(color.r, color.g, color.b, color.a);

		glPushMatrix();
		glTranslatef(currentPosition.x, currentPosition.y, currentPosition.z);
		glutSolidSphere(particle.GetSize(), 20, 20);
		glPopMatrix();
	}

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
