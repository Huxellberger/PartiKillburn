// Jake Huxell (C) 2017

#include "stdafx.h"
#include "PartiKillburnConstants.h"

#include <Dependencies/freeglut/freeglut.h>
#include <PartiKillburnLib/Source/Public/Engine/PartiKillburnEngine.h>
#include <PartiKillburnLib/Source/Public/Particle/Particle.h>
#include <PartiKillburnLib/Source/Public/Particle/ParticleSystem.h>
#include <PartiKillburnLib/Source/Public/Particle/Vector3.h>

#include <vector>

namespace PartiKillburn
{
	static ParticleSystemParams GetDefaultParticleParams()
	{
		return ParticleSystemParams(Bounds(Vector3(0.0f, 10.0f, -10.0f), Vector3(10.0f, 10.0f, 10.0f)), ParticleColor(100.0f, 255.0f, 0.0f, 1.0f), 1.0f, 3.0f, 0.5f, PartiKillburnConstants::DefaultParticleCount);
	}

	static PartiKillburnEngine Engine(ParticleSystem(GetDefaultParticleParams()), PartiKillburnConstants::UpdateSpeed);

	void Update()
	{
		Engine.Update();
	}
}

int main(int argc, char **argv) 
{
	// Remove console window
	FreeConsole();

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(PartiKillburnConstants::WindowPositionX, PartiKillburnConstants::WindowPositionY);
	glutInitWindowSize(PartiKillburnConstants::WindowSizeX, PartiKillburnConstants::WindowSizeY);
	glutCreateWindow("Christmas ALREADY?");

	glutDisplayFunc(PartiKillburn::Update);
	glutMainLoop();

	return 0;
}