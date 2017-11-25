// Jake Huxell (C) 2017

#pragma once

#include <Source/Public/Particle/Vector3.h>
#include <CppUnitTestAssert.h>

// ------------------------------------------------------------

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Vector3>(const Vector3& t)
{
	std::wstringstream stream;
	stream << t.x << ", " << t.y << ", " << t.z;
	return stream.str();
}

// ------------------------------------------------------------
