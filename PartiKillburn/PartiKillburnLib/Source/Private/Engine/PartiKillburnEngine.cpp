// Jake Huxell (C) 2017

#include "stdafx.h"
#include "PartiKillburnLib/Source/Public/Engine/PartiKillburnEngine.h"

#include "PartiKillburnLib/Source/Public/Engine/RandomGeneration.h"
#include <Dependencies/freeglut/freeglut.h>
#include <time.h>

// ------------------------------------------------------------

const float PartiKillburnEngine::MOVE_SPEED = 0.3f;

// ------------------------------------------------------------

PartiKillburnEngine::PartiKillburnEngine(const ParticleSystem& inSystem, const float inGroundYPosition, const std::vector<CollidableInterface*>& inCollidables)
	: collidables(inCollidables)
	, particleSystem(inSystem)
	, sun(ParticleParams(Vector3(-75.0f, 15.0f, -75.0f), 10.0f, false))
	, currentPosition(Vector3(0.0, 10.0f, 40.0f))
	, windDirection()
	, windDist(-14.0f, 14.0f)
	, groundYPosition(inGroundYPosition)
{
	PartiKillburnRandomGeneration::randomGenerator.seed((unsigned int) time(nullptr));
}

// ------------------------------------------------------------

void PartiKillburnEngine::Initialise()
{
	CreateMenu();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

// ------------------------------------------------------------

// Magnitude of said vector determines the strength.
void PartiKillburnEngine::SetWindDirection(Vector3 inWindDirection)
{
	windDirection = inWindDirection;
}

// ------------------------------------------------------------

void PartiKillburnEngine::Update(const float inDelta)
{
	UpdateLifetimes();
	UpdatePositions(inDelta);
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

void PartiKillburnEngine::UpdatePositions(const float inDelta)
{
	for (ParticleSystemCount currentParticle = 0; currentParticle < particleSystem.GetCurrentActiveParticles(); ++currentParticle)
	{
		if (!particleSystem.particles[currentParticle].resting)
		{
			particleSystem.particles[currentParticle].UpdatePosition(inDelta, windDirection);

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

			/*
			for (ParticleSystemCount possibleCollider = currentParticle + 1; possibleCollider < particleSystem.GetCurrentActiveParticles(); ++possibleCollider)
			{
				if (particleSystem.particles[currentParticle].HasCollided(particleSystem.particles[possibleCollider].currentPosition))
				{
					particleSystem.particles[currentParticle].SetSize(particleSystem.particles[currentParticle].GetSize() + particleSystem.particles[possibleCollider].GetSize());
					particleSystem.particles[possibleCollider].currentPosition = particleSystem.particles[possibleCollider].GetStartPosition();
				}
			}
			*/
		}
	}
}

// ------------------------------------------------------------

void PartiKillburnEngine::RenderParticles()
{
	SetView();
	glDisable(GL_LIGHTING);
	glDepthFunc(GL_LESS);

	auto&& color = particleSystem.GetParticleColor();
	auto&& collidableColor = ParticleColor(1.0f, 0.0f, 0.0f, 1.0f);
	auto&& groundColor = ParticleColor(0.0f, 1.0f, 0.0f, 1.0f);
	auto&& sunColor = ParticleColor(1.0f, 0.5f, 0.0f, 1.0f);

	// Sun
	sun.DrawCollidable(sunColor);

	// Ground
	glColor4f(groundColor.r, groundColor.g, groundColor.b, groundColor.a);

	glBegin(GL_POLYGON);
	glVertex3f(-100.0f, groundYPosition, -100.0f);
	glVertex3f(100.0f, groundYPosition, -30.0f);
	glVertex3f(100.0f, groundYPosition, 100.0f);
	glVertex3f(-100.0f, groundYPosition, 100.0f);
	glEnd();

	// Collidables
	for (std::vector<CollidableInterface*>::iterator it = collidables.begin(); it != collidables.end(); ++it)
	{
		(*it)->DrawCollidable(collidableColor);
	}

	// Particles
	for (ParticleSystemCount currentParticle = 0; currentParticle < particleSystem.GetCurrentActiveParticles(); ++currentParticle)
	{
		particleSystem.particles[currentParticle].DrawCollidable(color);
	}

	glutSwapBuffers();
}

// ------------------------------------------------------------

void PartiKillburnEngine::SetView()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(currentPosition.x, currentPosition.y, currentPosition.z, 0.0, -10.0, 0.0, 0.0, 1.0, 0.0);
}

// ------------------------------------------------------------

void PartiKillburnEngine::CreateMenu()
{
	glutAddMenuEntry("Reset", 1);
	glutAddMenuEntry("Increase Particles", 2);
	glutAddMenuEntry("Decrease Particles", 3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// ------------------------------------------------------------

void PartiKillburnEngine::OnMenuSelected(int selection)
{
	switch (selection)
	{
		case 1:
			particleSystem.Reset();
			break;
		case 2:
			particleSystem.IncreaseCapacity();
			break;
		case 3:
			particleSystem.DecreaseCapacity();
			break;
		case 4:
			exit(0);
			break;
		default:
			break;
	}
}

// ------------------------------------------------------------

void PartiKillburnEngine::OnKeyboardSelection(unsigned char key, int x, int y)
{
	switch (key)
	{
	// Escape
	case 27:
		exit(0);
		break;
	// w
	case 119:
		currentPosition.x += MOVE_SPEED;
		break;
	// a
	case 97:
		currentPosition.z -= MOVE_SPEED;
		break;
	// s
	case 115:
		currentPosition.x -= MOVE_SPEED;
		break;
	// d
	case 100:
		currentPosition.z += MOVE_SPEED;
		break;
	// x
	case 120:
		currentPosition.y += MOVE_SPEED;
		break;
	// z
	case 122:
		currentPosition.y -= MOVE_SPEED;
		break;
	// m
	case 109:
		particleSystem.IncreaseCapacity();
		break;
	// l
	case 108:
		particleSystem.DecreaseCapacity();
		break;
	// r
	case 114:
		particleSystem.Reset();
		break;
	// k
	case 107:
		particleSystem.MaxOutParticles();
		break;
	// o
	case 111:
		SetWindDirection
		(
			Vector3
			(
				(windDist(PartiKillburnRandomGeneration::randomGenerator) + windDist(PartiKillburnRandomGeneration::randomGenerator)) * 2.0f,
				0.0f,
				(windDist(PartiKillburnRandomGeneration::randomGenerator) + windDist(PartiKillburnRandomGeneration::randomGenerator)) * 2.0f
			)
		);
		particleSystem.Reset();
	default:
		break;
	}
}

// ------------------------------------------------------------
