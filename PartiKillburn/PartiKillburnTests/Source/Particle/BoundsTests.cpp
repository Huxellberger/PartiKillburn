// Jake Huxell (C) 2017

#include "stdafx.h"
#include "CppUnitTest.h"

#include "Source/Particle/VectorTestFunctions.h"

#include <Source/Public/Engine/PartiKillburnEngine.h>
#include <Source/Public/Engine/RandomGeneration.h>
#include <Source/Public/Particle/Bounds.h>
#include <Source/Public/Particle/Vector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ------------------------------------------------------------

namespace BoundsTestFixture
{
	TEST_CLASS(BoundsFixture)
	{
	public:

		TEST_METHOD(GetRandomPoint_LiesWithinBounds)
		{
			const Vector3 expectedBottomVector = Vector3(-1.5f, -3.1f, -1.0f);
			const Vector3 expectedTopVector = Vector3(3.5f, 2.1f, 1.0f);

			PartiKillburnRandomGeneration::randomGenerator.seed(2u);
			auto testBounds = Bounds(expectedBottomVector, expectedTopVector);

			auto&& generatedPoint = testBounds.GetRandomPoint();
			Assert::IsTrue(generatedPoint.x <= expectedTopVector.x && generatedPoint.x >= expectedBottomVector.x);
			Assert::IsTrue(generatedPoint.y <= expectedTopVector.y && generatedPoint.y >= expectedBottomVector.y);
			Assert::IsTrue(generatedPoint.z <= expectedTopVector.z && generatedPoint.z >= expectedBottomVector.z);
		}

		TEST_METHOD(GetStartExtent_ReturnsStartExtent)
		{
			const Vector3 expectedBottomVector = Vector3(-1.5f, -3.1f, -1.0f);
			const Vector3 expectedTopVector = Vector3(3.5f, 2.1f, 1.0f);

			PartiKillburnRandomGeneration::randomGenerator.seed(2u);
			auto testBounds = Bounds(expectedBottomVector, expectedTopVector);

			auto&& generatedPoint = testBounds.GetRandomPoint();
			Assert::AreEqual(expectedBottomVector, testBounds.GetStartExtent());
		}

		TEST_METHOD(GetEndExtent_ReturnsEndExtent)
		{
			const Vector3 expectedBottomVector = Vector3(-1.5f, -3.1f, -1.0f);
			const Vector3 expectedTopVector = Vector3(3.5f, 2.1f, 1.0f);

			auto testBounds = Bounds(expectedBottomVector, expectedTopVector);

			Assert::AreEqual(expectedTopVector, testBounds.GetEndExtent());
		}

		TEST_METHOD(GetCentre_ReturnsMidpoint)
		{
			const Vector3 startExtent = Vector3(-1.5f, -3.1f, -1.0f);
			const Vector3 endExtent = Vector3(3.5f, 2.1f, 1.0f);

			const Vector3 midpointVector = Vector3(((startExtent.x + endExtent.x) * 0.5f), ((startExtent.y + endExtent.y) * 0.5f), ((startExtent.z + endExtent.z) * 0.5f));

			auto testBounds = Bounds(startExtent, endExtent);

			Assert::AreEqual(midpointVector, testBounds.GetCentre());
		}
	};
}

// ------------------------------------------------------------
