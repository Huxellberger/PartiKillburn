// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"

#include "Source/Engine/TestPartiKillburnEngine.h"

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
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>( new TestPartiKillburnEngine(expectedDelta));

			Assert::AreEqual(expectedDelta, testEngine->GetTimeDelta());
		}

		TEST_METHOD(Update_CallsCorrectUpdates)
		{
			auto&& testEngine = std::unique_ptr<TestPartiKillburnEngine>(new TestPartiKillburnEngine(3.0f));
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
