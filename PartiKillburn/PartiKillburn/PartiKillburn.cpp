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
	static std::vector<ParticleParams> GetDefaultParticleParams()
	{
		return std::vector<ParticleParams>{ ParticleParams(Vector3(1.0f, 2.0f, 3.0f), 1.0f, false) };
	}

	static PartiKillburnEngine Engine(ParticleSystem(GetDefaultParticleParams(), PartiKillburnConstants::DefaultParticleCount), PartiKillburnConstants::UpdateSpeed);

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