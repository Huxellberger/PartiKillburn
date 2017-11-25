// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"
#include "Source/Particle/VectorTestFunctions.h"

#include <Source/Public/Particle/Particle.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ------------------------------------------------------------

namespace ParticleTestFixture
{
	TEST_CLASS(ParticleFixture)
	{
	public:

		TEST_METHOD(Created_StartingParamsAreCorrect)
		{
			const Vector3 expectedVector = Vector3(3.5f, 2.1f, 1.0f);
			auto testParticle = Particle(ParticleParams(expectedVector, 1.0f, false));

			Assert::AreEqual(expectedVector, testParticle.currentPosition);
			Assert::IsFalse(testParticle.resting);
		}

		TEST_METHOD(GetSize_MatchesChosenSize)
		{
			const float selectedSize = 2.5f;
			auto testParticle = Particle(ParticleParams(Vector3(), selectedSize, true));

			Assert::AreEqual(selectedSize, testParticle.GetSize());
		}

		TEST_METHOD(CanDrift_SetTrue_True)
		{
			auto testParticle = Particle(ParticleParams(Vector3(), 0.0f, true));

			Assert::IsTrue(testParticle.CanDrift());
		}

		TEST_METHOD(CanDrift_SetFalse_False)
		{
			auto testParticle = Particle(ParticleParams(Vector3(), 0.0f, false));

			Assert::IsFalse(testParticle.CanDrift());
		}
	};
}

// ------------------------------------------------------------
