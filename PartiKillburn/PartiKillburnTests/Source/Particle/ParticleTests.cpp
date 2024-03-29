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

			Assert::AreEqual(expectedVector, testParticle.GetStartPosition());
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

		TEST_METHOD(UpdatePosition__WindModified_CalculatesExpectedNewPositionViaVerletIntegrationAndScaledBySize)
		{
			const float particleSize = 1.5f;
			auto testParticle = Particle(ParticleParams(Vector3(), particleSize, true));
			const Vector3 wind = Vector3(50.0f, 10.0f, 30.0f);
			const float timeDelta = 2.0f;
			const float timeDeltaSquared = timeDelta * timeDelta;

			const Vector3 expectedPosition = Vector3((wind.x * 1.f / particleSize) * timeDeltaSquared, PartiKillburnEngineConstants::GRAVITY * timeDeltaSquared, (wind.z * 1.f / particleSize) * timeDeltaSquared);
			testParticle.UpdatePosition(timeDelta, wind);

			Assert::IsTrue(VectorAssertionHelpers::AreVectorsNearlyEqual(expectedPosition, testParticle.currentPosition, 0.3f));
		}

		TEST_METHOD(UpdatePosition__NotModifiedByWind_CalculatesExpectedNewPositionViaVerletIntegration)
		{
			auto testParticle = Particle(ParticleParams(Vector3(), 1.0f, false));
			const Vector3 wind = Vector3(10.0f, 10.0f, 10.0f);
			const float timeDelta = 2.0f;
			const float timeDeltaSquared = timeDelta * timeDelta;

			const Vector3 expectedPosition = Vector3(0.0f, PartiKillburnEngineConstants::GRAVITY * timeDeltaSquared, 0.0f);
			testParticle.UpdatePosition(timeDelta, wind);

			Assert::AreEqual(expectedPosition, testParticle.currentPosition);
		}

		TEST_METHOD(HasCollided_PointOutsideRadius_False)
		{
			auto testParticle = Particle(ParticleParams(Vector3(), 10.0f, false));

			Assert::IsFalse(testParticle.HasCollided(Vector3(10.1f, 10.1f, 10.1f)));
		}

		TEST_METHOD(HasCollided_PointInsideRadius_True)
		{
			auto testParticle = Particle(ParticleParams(Vector3(), 10.0f, false));

			Assert::IsTrue(testParticle.HasCollided(Vector3(4.9f, 4.9f, 4.9f)));
		}
	};
}

// ------------------------------------------------------------
