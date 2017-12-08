// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Particle/ParticleColor.h"
#include "PartiKillburnLib/Source/Public/Particle/Vector3.h"

class CollidableInterface
{
public:
	
	virtual bool HasCollided(const Vector3& inPoint) const = 0;
	virtual void DrawCollidable(const ParticleColor& inColor) = 0;
};