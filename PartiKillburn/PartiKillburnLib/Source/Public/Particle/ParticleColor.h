// Jake Huxell (C) 2017

#pragma once

struct ParticleColor
{
	ParticleColor()
		: ParticleColor(0.0f, 0.0f, 0.0f, 0.0f)
	{
	}

	ParticleColor(float inR, float inG, float inB, float inA)
		: r(inR)
		, g(inG)
		, b(inB)
		, a(inA)
	{
	}

	inline bool operator==(const ParticleColor& other) const
	{
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	inline bool operator!=(const ParticleColor& other) const
	{
		return !(*this == other);
	}

	float r;
	float g;
	float b;
	float a;
};
