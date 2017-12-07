// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"
#include "Source/Particle/ParticleColorTestFunctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ------------------------------------------------------------

namespace ParticleColorTestFixture
{
	TEST_CLASS(ParticleColorFixture)
	{
	public:

		TEST_METHOD(Created_NoParams_ZeroColor)
		{
			const auto currentColor = ParticleColor();

			Assert::AreEqual(0.0f, currentColor.r);
			Assert::AreEqual(0.0f, currentColor.g);
			Assert::AreEqual(0.0f, currentColor.b);
			Assert::AreEqual(0.0f, currentColor.a);
		}

		TEST_METHOD(Created_StartingParamsAreCorrect)
		{
			const float expectedR = 3.5f;
			const float expectedG = 11.1f;
			const float expectedB = -1.0f;
			const float expectedA = 1.0f;

			const auto currentColor = ParticleColor(expectedR, expectedG, expectedB, expectedA);

			Assert::AreEqual(expectedR, currentColor.r);
			Assert::AreEqual(expectedG, currentColor.g);
			Assert::AreEqual(expectedB, currentColor.b);
			Assert::AreEqual(expectedA, currentColor.a);
		}

		TEST_METHOD(Equal_FieldsMatch_True)
		{
			const float expectedR = 3.5f;
			const float expectedG = 11.1f;
			const float expectedB = -1.0f;
			const float expectedA = 1.0f;

			const auto currentColor = ParticleColor(expectedR, expectedG, expectedB, expectedA);
			const auto otherColor = ParticleColor(expectedR, expectedG, expectedB, expectedA);

			Assert::AreEqual(currentColor, otherColor);
		}

		TEST_METHOD(Equal_FieldsDoNotMatch_False)
		{
			const float expectedR = 3.5f;
			const float expectedG = 11.1f;
			const float expectedB = -1.0f;
			const float expectedA = 1.0f;

			const auto currentColor = ParticleColor(expectedR -1.0f, expectedG, expectedB, expectedA);
			const auto otherColor = ParticleColor(expectedR, expectedG, expectedB, expectedA);

			Assert::AreNotEqual(currentColor, otherColor);
		}
	};
}

// ------------------------------------------------------------
