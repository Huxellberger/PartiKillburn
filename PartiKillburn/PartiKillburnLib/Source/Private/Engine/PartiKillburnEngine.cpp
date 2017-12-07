// Jake Huxell (C) 2017

#include "stdafx.h"
#include "PartiKillburnLib/Source/Public/Engine/PartiKillburnEngine.h"

#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"
#include <Dependencies/freeglut/freeglut.h>
#include <time.h>

// ------------------------------------------------------------

PartiKillburnEngine::PartiKillburnEngine(const ParticleSystem& inSystem, float inUpdateDeltaSeconds)
	: particleSystem(inSystem)
	, windDirection()
	, updateDeltaSeconds(inUpdateDeltaSeconds)
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
		particleSystem.particles[currentParticle].UpdatePosition(updateDeltaSeconds, windDirection);
	}
}

// ------------------------------------------------------------

void PartiKillburnEngine::RenderParticles()
{
	SetView();
	glDisable(GL_LIGHTING);

	auto&& color = particleSystem.GetParticleColor();
	glColor4f(color.r, color.g, color.b, color.a);

	for (ParticleSystemCount currentParticle = 0; currentParticle < particleSystem.GetCurrentActiveParticles(); ++currentParticle)
	{
		glPushMatrix();
		auto&& particle = particleSystem.particles[currentParticle];
		auto&& position = particle.currentPosition;
		glTranslatef(position.x, position.y, position.z);

		/*
		glBegin(GL_POINTS);
		glVertex3f(position.x, position.y, position.z);
		glEnd();
		*/

		glutSolidSphere(particle.GetSize(), 20, 20);
		glPopMatrix();
	}


	glutSwapBuffers();
}

void PartiKillburnEngine::SetView()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0, 30, 0.0, -10.0, 0.0, 0.0, 1.0, 0.0);
}

// ------------------------------------------------------------
