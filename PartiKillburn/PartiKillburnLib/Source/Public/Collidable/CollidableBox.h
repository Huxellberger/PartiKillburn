// Jake Huxell (C) 2017

#pragma once

#include "PartiKillburnLib/Source/Public/Collidable/CollidableInterface.h"
#include "PartiKillburnLib/Source/Public/Particle/Bounds.h"

#include <Dependencies/freeglut/freeglut.h>

class CollidableBox
	: public CollidableInterface
{
public:

	CollidableBox(const Bounds& inBounds);

	// CollidableInterface
	virtual inline bool HasCollided(const Vector3& inPoint) const override final
	{
		const Vector3 startExtent = boxExtent.GetStartExtent();
		const Vector3 endExtent = boxExtent.GetEndExtent();

		return ((inPoint.x >= startExtent.x && inPoint.x <= endExtent.x) || (inPoint.x >= endExtent.x && inPoint.x <= startExtent.x))
			&& ((inPoint.y >= startExtent.y && inPoint.y <= endExtent.y) || (inPoint.y >= endExtent.y && inPoint.y <= startExtent.y))
			&& ((inPoint.z >= startExtent.z && inPoint.z <= endExtent.z) || (inPoint.z >= endExtent.z && inPoint.z <= startExtent.z));
	}

	virtual inline void DrawCollidable(const ParticleColor& inColor) override final
	{
		glColor4f(inColor.r, inColor.g, inColor.b, inColor.a);

		auto&& startPoint = boxExtent.GetStartExtent();
		auto&& endPoint = boxExtent.GetEndExtent();

		glBegin(GL_POLYGON);
		glVertex3f(startPoint.x, startPoint.y, startPoint.z);
		glVertex3f(endPoint.x, startPoint.y, startPoint.z);
		glVertex3f(startPoint.x, endPoint.y, startPoint.z);
		glVertex3f(endPoint.x, endPoint.y, startPoint.z);
		glVertex3f(startPoint.x, startPoint.y, endPoint.z);
		glVertex3f(endPoint.x, startPoint.y, endPoint.z);
		glVertex3f(startPoint.x, endPoint.y, endPoint.z);
		glVertex3f(endPoint.x, endPoint.y, endPoint.z);
		glEnd();
	}
	// ~CollidableInterface

private:

	Bounds boxExtent;
};
