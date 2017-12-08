// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"
#include "Source/Particle/ParticleColorTestFunctions.h"
#include "Source/Particle/VectorTestFunctions.h"

#include <Source/Public/Particle/Particle.h>
#include <Source/Public/Particle/ParticleSystem.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ------------------------------------------------------------

namespace ParticleSystemTestFixture
{
	TEST_CLASS(ParticleSystemFixture)
	{
	public:

		const Vector3 boundsLow = Vector3(-1.0f, 2.0f, -5.0f);
		const Vector3 boundsHigh = Vector3(3.0f, 7.0f, 11.0f);
		const ParticleColor expectedColor = ParticleColor(1.0f, 1.0f, 1.0f, 3.0f);
		const float minSize = 1.1f;
		const float maxSize = 11.0f;
		const ParticleSystemCount maxCount = 11u;

		const ParticleSystemParams GetParams() const
		{
			return ParticleSystemParams(Bounds(boundsLow, boundsHigh), expectedColor, minSize, maxSize, 0.0f, maxCount);
		}

		TEST_METHOD(Created_NoParticles)
		{
			auto particleSystem = ParticleSystem(GetParams());

			Assert::AreEqual(0u, particleSystem.GetCurrentActiveParticles());
		}

		TEST_METHOD(Created_CorrectColor)
		{
			auto particleSystem = ParticleSystem(GetParams());

			Assert::AreEqual(expectedColor, particleSystem.GetParticleColor());
		}

		TEST_METHOD(AddParticles_AddsParticlesOfCount)
		{
			const ParticleSystemCount expectedNumber = maxCount - 3;
			auto particleSystem = ParticleSystem(GetParams());
			particleSystem.AddParticles(expectedNumber);

			Assert::AreEqual(expectedNumber, particleSystem.GetCurrentActiveParticles());
		}

		TEST_METHOD(AddParticles_ParticleCreatedOfCorrectType)
		{
			auto particleSystem = ParticleSystem(GetParams());
			particleSystem.AddParticles(1);

			Assert::IsTrue(particleSystem.particles[0].currentPosition.x <= boundsHigh.x && particleSystem.particles[0].currentPosition.x >= boundsLow.x);
			Assert::IsTrue(particleSystem.particles[0].currentPosition.y <= boundsHigh.y && particleSystem.particles[0].currentPosition.y >= boundsLow.y);
			Assert::IsTrue(particleSystem.particles[0].currentPosition.z <= boundsHigh.z && particleSystem.particles[0].currentPosition.z >= boundsLow.z);
		}

		TEST_METHOD(AddParticles_CreatesParticlesUntilSizeExceeded)
		{
			auto particleSystem = ParticleSystem(GetParams());

			particleSystem.AddParticles(maxCount + 100);

			Assert::AreEqual(maxCount, particleSystem.GetCurrentActiveParticles());
		}

		TEST_METHOD(IncreaseCapacity_MaxCountMultipliedBy10)
		{
			auto particleSystem = ParticleSystem(GetParams());

			particleSystem.IncreaseCapacity();

			Assert::AreEqual(GetParams().maxParticles * 10u, particleSystem.GetCapacity());
		}

		TEST_METHOD(DecreaseCapacity_MaxCountHalvedAndCurrentReducedToFit)
		{
			auto particleSystem = ParticleSystem(GetParams());

			particleSystem.AddParticles(maxCount + 100);
			particleSystem.DecreaseCapacity();

			Assert::AreEqual((ParticleSystemCount)(GetParams().maxParticles * 0.5), particleSystem.GetCapacity());
			Assert::AreEqual(0u, particleSystem.GetCurrentActiveParticles());
		}

		TEST_METHOD(Reset_ParticleCountBackToZero)
		{
			auto particleSystem = ParticleSystem(GetParams());

			particleSystem.AddParticles(maxCount + 100);
			particleSystem.Reset();

			Assert::AreEqual(0u, particleSystem.GetCurrentActiveParticles());
		}
	};
}

// ------------------------------------------------------------
