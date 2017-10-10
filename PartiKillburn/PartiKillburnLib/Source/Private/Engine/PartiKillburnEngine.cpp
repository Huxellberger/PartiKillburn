// Jake Huxell (C) 2017

#include "stdafx.h"
#include "Source/Public/Engine/PartiKillburnEngine.h"
#include <Dependencies/freeglut/freeglut.h>

// ------------------------------------------------------------

PartiKillburnEngine::PartiKillburnEngine(const float inUpdateDelta)
	: updateDelta(inUpdateDelta)
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
