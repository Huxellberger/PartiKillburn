// Jake Huxell (C) 2017

#include "stdafx.h"
#include "PartiKillburnConstants.h"

#include <Dependencies/freeglut/freeglut.h>
#include <PartiKillburnLib/Source/Public/Collidable/CollidableBox.h>
#include <PartiKillburnLib/Source/Public/Engine/PartiKillburnEngine.h>
#include <PartiKillburnLib/Source/Public/Particle/Particle.h>
#include <PartiKillburnLib/Source/Public/Particle/ParticleSystem.h>
#include <PartiKillburnLib/Source/Public/Particle/Vector3.h>

#include <chrono>
#include <thread>
#include <vector>

namespace PartiKillburn
{
	static ParticleSystemParams GetDefaultParticleParams()
	{
		return ParticleSystemParams(Bounds(Vector3(-30.0f, 5.0f, -20.0f), Vector3(30.0f, 5.0f, 15.0f)), ParticleColor(1.0f, 1.0f, 1.0f, 1.0f), 0.2f, 1.7f, 1.0f, PartiKillburnConstants::DefaultParticleCount);
	}

	static std::vector<CollidableInterface*> GetCollidables()
	{
		return std::vector<CollidableInterface*>{new CollidableBox(Bounds(Vector3(0.0f, PartiKillburnConstants::GroundPosition, 0.0f), Vector3(10.0f, -10.0f, 5.0f)))};
	}

	static PartiKillburnEngine Engine(ParticleSystem(GetDefaultParticleParams()), PartiKillburnConstants::UpdateSpeedSeconds, PartiKillburnConstants::GroundPosition, GetCollidables());

	static int menuId;

	void OnSelection(int selection)
	{
		Engine.OnMenuSelected(selection);
	}

	void Init()
	{
		menuId = glutCreateMenu(PartiKillburn::OnSelection);
		Engine.Initialise(); glutSetMenu(menuId);
	}

	void Update()
	{
		auto&& startTime = std::chrono::high_resolution_clock::now();
		Engine.Update();
		auto&& endTime = std::chrono::high_resolution_clock::now();
		auto&& timespan = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
		if (timespan.count() < PartiKillburnConstants::UpdateSpeedSeconds)
		{
			const long sleepTime = (long)((PartiKillburnConstants::UpdateSpeedSeconds - timespan.count()) * 1000);
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
		}
		else
		{
			// Update is too short, scale to make sure we can complete all of it in time
			PartiKillburnConstants::UpdateSpeedSeconds *= 2.0f;
		}
	}

	void Input(unsigned char key, int x, int y)
	{
		Engine.OnKeyboardSelection(key, x, y);
	}

	void Resize(int w, int h)
	{
		Engine.Resize(w, h);
	}

	void Idle()
	{
		glutPostRedisplay();
	}
}

int main(int argc, char **argv) 
{
	// Remove console window
	FreeConsole();

	PartiKillburn::Engine.SetWindDirection(PartiKillburnConstants::WindDirection);

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(PartiKillburnConstants::WindowPositionX, PartiKillburnConstants::WindowPositionY);
	glutInitWindowSize(PartiKillburnConstants::WindowSizeX, PartiKillburnConstants::WindowSizeY);
	glutCreateWindow("Christmas ALREADY?");
	glutFullScreen();
	PartiKillburn::Init();

	glutDisplayFunc(PartiKillburn::Update);
	glutReshapeFunc(PartiKillburn::Resize);
	glutKeyboardFunc(PartiKillburn::Input);
	glutIdleFunc(PartiKillburn::Idle);
	glutMainLoop();

	return 0;
}