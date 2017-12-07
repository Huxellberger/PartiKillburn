// Jake Huxell (C) 2017

#pragma once

#include <Source/Public/Particle/Vector3.h>
#include <CppUnitTestAssert.h>

// ------------------------------------------------------------

namespace VectorAssertionHelpers
{
	static bool AreVectorsNearlyEqual(const Vector3& lhs, const Vector3& rhs, const float tolerance)
	{
		return abs(lhs.x - rhs.x) < tolerance && abs(lhs.y - rhs.y) < tolerance && abs(lhs.z - rhs.z) < tolerance;
	}
}

// ------------------------------------------------------------

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Vector3>(const Vector3& t)
{
	std::wstringstream stream;
	stream << t.x << ", " << t.y << ", " << t.z;
	return stream.str();
}

// ------------------------------------------------------------
