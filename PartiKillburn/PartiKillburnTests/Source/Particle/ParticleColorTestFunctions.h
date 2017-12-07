// Jake Huxell (C) 2017

#pragma once

#include <Source/Public/Particle/ParticleColor.h>
#include <CppUnitTestAssert.h>

// ------------------------------------------------------------

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<ParticleColor>(const ParticleColor& t)
{
	std::wstringstream stream;
	stream << t.r << ", " << t.g << ", " << t.b << ", " << t.a;
	return stream.str();
}

// ------------------------------------------------------------
