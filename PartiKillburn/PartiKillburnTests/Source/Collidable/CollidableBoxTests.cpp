// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"

#include <PartiKillburnLib/Source/Public/Collidable/CollidableBox.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ------------------------------------------------------------

namespace CollidableBoxTestFixture
{
	TEST_CLASS(CollidableBoxFixture)
	{
	public:

		TEST_METHOD(HasCollided_OutsideBounds_False)
		{
			const Vector3 expectedBottomVector = Vector3(-1.5f, -3.1f, -1.0f);
			const Vector3 expectedTopVector = Vector3(3.5f, 2.1f, 1.0f);

			const CollidableBox testBox = CollidableBox(Bounds(expectedBottomVector, expectedTopVector));

			Assert::IsFalse(testBox.HasCollided(Vector3(expectedBottomVector.x - 1.0f, expectedBottomVector.y, expectedBottomVector.z)));
		}

		TEST_METHOD(HasCollided_InsideBounds_True)
		{
			const Vector3 expectedBottomVector = Vector3(-1.5f, -3.1f, -1.0f);
			const Vector3 expectedTopVector = Vector3(3.5f, 2.1f, 1.0f);

			const Bounds boxBounds = Bounds(expectedBottomVector, expectedTopVector);

			const CollidableBox testBox = CollidableBox(boxBounds);

			Assert::IsTrue(testBox.HasCollided(boxBounds.GetCentre()));
		}
	};
}

// ------------------------------------------------------------
