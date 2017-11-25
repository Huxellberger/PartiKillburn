// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"
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

		static std::vector<ParticleParams> GetParams()
		{
			return std::vector<ParticleParams>
			{ 
				ParticleParams(Vector3(1.0f, 3.0f, 4.0f), 1.0f, true), 
				ParticleParams(Vector3(2.0f, 5.0f, 2.0f), 3.0f, false)
			};
		}

		TEST_METHOD(Created_NoParticles)
		{
			auto particleSystem = ParticleSystem(GetParams(), 100);

			Assert::AreEqual(0u, particleSystem.GetCurrentActiveParticles());
		}

		TEST_METHOD(Update_AddsParticle)
		{
			auto particleSystem = ParticleSystem(GetParams(), 100);
			particleSystem.Update();

			Assert::AreEqual(1u, particleSystem.GetCurrentActiveParticles());
		}

		TEST_METHOD(Update_ParticleCreatedOfCorrectType)
		{
			auto&& params = GetParams();
			auto particleSystem = ParticleSystem(params, 100);
			particleSystem.Update();

			Assert::AreEqual(params[0].startPosition, particleSystem.particles[0].currentPosition);
		}

		TEST_METHOD(Update_CreatesParticlesUntilSizeExceeded)
		{
			const ParticleSystemCount maxCount = 10;
			auto particleSystem = ParticleSystem(GetParams(), maxCount);

			for (unsigned i = 0u; i <= maxCount + 1; ++i)
			{
				particleSystem.Update();
			}

			Assert::AreEqual(maxCount, particleSystem.GetCurrentActiveParticles());
		}

		TEST_METHOD(UpdateMultiples_CreatesParticlesOfCorrectType)
		{
			auto&& params = GetParams();
			auto particleSystem = ParticleSystem(params, 100);

			particleSystem.Update();
			particleSystem.Update();

			Assert::AreEqual(params[1].startPosition, particleSystem.particles[1].currentPosition);
		}

		TEST_METHOD(UpdateMultiples_LoopsTypeBackAround)
		{
			auto&& params = GetParams();
			auto particleSystem = ParticleSystem(params, 100);

			for each(auto&& param in params)
			{
				particleSystem.Update();
			}

			particleSystem.Update();

			Assert::AreEqual(params[0].startPosition, particleSystem.particles[params.size()].currentPosition);
		}
	};
}

// ------------------------------------------------------------
