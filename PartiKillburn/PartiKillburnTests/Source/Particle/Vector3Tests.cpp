// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"
#include "Source/Particle/VectorTestFunctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ------------------------------------------------------------

namespace Vector3TestFixture
{
	TEST_CLASS(Vector3Fixture)
	{
	public:

		TEST_METHOD(Created_NoParams_ZeroVector)
		{
			const Vector3 currentVector = Vector3();

			Assert::AreEqual(0.0f, currentVector.x);
			Assert::AreEqual(0.0f, currentVector.y);
			Assert::AreEqual(0.0f, currentVector.z);
		}

		TEST_METHOD(Created_StartingParamsAreCorrect)
		{
			const float expectedX = 3.5f;
			const float expectedY = 11.1f;
			const float expectedZ = -1.0f;

			const Vector3 currentVector = Vector3(expectedX, expectedY, expectedZ);

			Assert::AreEqual(expectedX, currentVector.x);
			Assert::AreEqual(expectedY, currentVector.y);
			Assert::AreEqual(expectedZ, currentVector.z);
		}

		TEST_METHOD(Equal_FieldsMatch_True)
		{
			const float expectedX = 3.5f;
			const float expectedY = 11.1f;
			const float expectedZ = -1.0f;

			const Vector3 currentVector = Vector3(expectedX, expectedY, expectedZ);
			const Vector3 otherVector = Vector3(expectedX, expectedY, expectedZ);

			Assert::AreEqual(currentVector, otherVector);
		}

		TEST_METHOD(Equal_FieldsDoNotMatch_False)
		{
			const float expectedX = 3.5f;
			const float expectedY = 11.1f;
			const float expectedZ = -1.0f;

			const Vector3 currentVector = Vector3(expectedX, expectedY, expectedZ);
			const Vector3 otherVector = Vector3(expectedX - 1.0f, expectedY, expectedZ);

			Assert::AreNotEqual(currentVector, otherVector);
		}

		TEST_METHOD(Scale_ReturnsScaledVector)
		{
			const float expectedX = 3.5f;
			const float expectedY = 11.1f;
			const float expectedZ = -1.0f;

			const float scalingFactor = 2.0f;

			Vector3 currentVector = Vector3(expectedX, expectedY, expectedZ);

			Assert::AreEqual(currentVector.Scale(scalingFactor), Vector3(expectedX * scalingFactor, expectedY * scalingFactor, expectedZ * scalingFactor));
		}

		TEST_METHOD(Addition_WorksAsExpected)
		{
			const float expectedX = 3.5f;
			const float expectedY = 11.1f;
			const float expectedZ = -1.0f;

			Vector3 summedVector = Vector3(expectedX, expectedY, expectedZ);
			Vector3 matchingVector = Vector3(expectedX, expectedY, expectedZ);

			summedVector += matchingVector;

			Assert::AreEqual(matchingVector.Scale(2), summedVector);
		}

		TEST_METHOD(StaticAddition_WorksAsExpected)
		{
			const float expectedX = 3.5f;
			const float expectedY = 11.1f;
			const float expectedZ = -1.0f;

			const float otherExpectedX = 3.5f;
			const float otherExpectedY = 11.1f;
			const float otherExpectedZ = -1.0f;

			const Vector3 firstVector = Vector3(expectedX, expectedY, expectedZ);
			const Vector3 otherVector = Vector3(otherExpectedX, otherExpectedY, otherExpectedZ);

			const Vector3 SumVector = firstVector + otherVector;

			Assert::AreEqual(SumVector.x, firstVector.x + otherVector.x);
			Assert::AreEqual(SumVector.y, firstVector.y + otherVector.y);
			Assert::AreEqual(SumVector.z, firstVector.z + otherVector.z);
		}

		TEST_METHOD(Subtraction_WorksAsExpected)
		{
			const float expectedX = 3.5f;
			const float expectedY = 11.1f;
			const float expectedZ = -1.0f;

			Vector3 summedVector = Vector3(expectedX, expectedY, expectedZ);
			Vector3 matchingVector = Vector3(expectedX, expectedY, expectedZ);

			summedVector -= matchingVector;

			Assert::AreEqual(Vector3(), summedVector);
		}

		TEST_METHOD(StaticSubtraction_WorksAsExpected)
		{
			const float expectedX = 3.5f;
			const float expectedY = 11.1f;
			const float expectedZ = -1.0f;

			const float otherExpectedX = 3.5f;
			const float otherExpectedY = 11.1f;
			const float otherExpectedZ = -1.0f;

			const Vector3 firstVector = Vector3(expectedX, expectedY, expectedZ);
			const Vector3 otherVector = Vector3(otherExpectedX, otherExpectedY, otherExpectedZ);

			const Vector3 SumVector = firstVector - otherVector;

			Assert::AreEqual(SumVector.x, firstVector.x - otherVector.x);
			Assert::AreEqual(SumVector.y, firstVector.y - otherVector.y);
			Assert::AreEqual(SumVector.z, firstVector.z - otherVector.z);
		}
	};
}

// ------------------------------------------------------------
