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

		TEST_METHOD(Created_SetsCorrectTimeDelta)
		{
			const float expectedDelta = 1.2f;
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>( new TestPartiKillburnEngine(ParticleSystem(), expectedDelta));

			Assert::AreEqual(expectedDelta, testEngine->GetTimeDelta());
		}

		TEST_METHOD(Created_SetsCorrectParticleSystem)
		{
			const auto expectedSystem = ParticleSystem(std::vector<ParticleParams>(), 12u);

			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(expectedSystem, 1.1f));;
			
			Assert::AreEqual(expectedSystem.GetCurrentActiveParticles(), testEngine->GetParticleSystem().GetCurrentActiveParticles());
		}

		TEST_METHOD(Created_WindIsZeroVector)
		{
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(ParticleSystem(), 1.1f));

			Assert::AreEqual(Vector3(), testEngine->GetWindDirection());
		}

		TEST_METHOD(SetWindDirection_WindIsMatching)
		{
			const Vector3 expectedWind = Vector3(1.2f, 3.4f, -1.2f);
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(ParticleSystem(), 1.1f));

			testEngine->SetWindDirection(expectedWind);

			Assert::AreEqual(expectedWind, testEngine->GetWindDirection());
		}

		TEST_METHOD(Update_CallsCorrectUpdates)
		{
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(ParticleSystem(), .0f));
			testEngine->Update();

			Assert::IsTrue(testEngine->updateLifetimesCalled);
			Assert::IsTrue(testEngine->updateVelocitiesCalled);
			Assert::IsTrue(testEngine->updatePositionsCalled);
			Assert::IsTrue(testEngine->sortAlphaBlendingCalled);
			Assert::IsTrue(testEngine->transferTextureDataCalled);
			Assert::IsTrue(testEngine->renderParticlesCalled);
		}
	};
}

// ------------------------------------------------------------
