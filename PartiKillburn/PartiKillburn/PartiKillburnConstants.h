// Jake Huxell (C) 2017

#pragma once

#include <PartiKillburnLib/Source/Public/Particle/ParticleSystem.h>
#include <PartiKillburnLib/Source/Public/Particle/Vector3.h>

namespace PartiKillburnConstants
{
	static float UpdateSpeedSeconds = 0.003f;
	static ParticleSystemCount DefaultParticleCount = 10000;
	static Vector3 WindDirection = Vector3(10.0f, 0.0f, -2.0f);
	static int WindowPositionX = 100;
	static int WindowPositionY = 100;
	static int WindowSizeX = 600;
	static int WindowSizeY = 400;
}
