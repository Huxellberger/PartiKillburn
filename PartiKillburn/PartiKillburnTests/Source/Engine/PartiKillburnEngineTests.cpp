// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"

#include "Source/Engine/TestPartiKillburnEngine.h"
#include "Source/Particle/VectorTestFunctions.h"
#include <Source/Public/Engine/PartiKillburnEngine.h>

#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ------------------------------------------------------------

namespace PartiKillburnEngineTestFixture
{
	TEST_CLASS(PartiKillburnEngineFixture)
	{
	public:
		TEST_METHOD(Created_SetsCorrectParticleSystem)
		{
			const auto expectedSystem = ParticleSystem(ParticleSystemParams());

			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(expectedSystem));;
			
			Assert::AreEqual(expectedSystem.GetCurrentActiveParticles(), testEngine->GetParticleSystem().GetCurrentActiveParticles());
		}

		TEST_METHOD(Created_WindIsZeroVector)
		{
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(ParticleSystem()));

			Assert::AreEqual(Vector3(), testEngine->GetWindDirection());
		}

		TEST_METHOD(SetWindDirection_WindIsMatching)
		{
			const Vector3 expectedWind = Vector3(1.2f, 3.4f, -1.2f);
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(ParticleSystem()));

			testEngine->SetWindDirection(expectedWind);

			Assert::AreEqual(expectedWind, testEngine->GetWindDirection());
		}

		TEST_METHOD(Update_CallsCorrectUpdates)
		{
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(ParticleSystem()));
			testEngine->Update(0.1f);

			Assert::IsTrue(testEngine->updateLifetimesCalled);
			Assert::IsTrue(testEngine->updatePositionsCalled);
			Assert::IsTrue(testEngine->renderParticlesCalled);
		}
	};
}

// ------------------------------------------------------------
