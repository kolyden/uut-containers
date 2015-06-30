#include "uutColor.h"

namespace uut
{
	const Color4f Color4f::BLACK(0, 0, 0);
	const Color4f Color4f::WHITE(1, 1, 1);

	Color4f::Color4f() {}

	Color4f::Color4f(float _r, float _g, float _b)
		: r(_r), g(_g), b(_b), a(1.0f)
	{
	}

	Color4f::Color4f(float _r, float _g, float _b, float _a)
		: r(_r), g(_g), b(_b), a(_a)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	const Color4b Color4b::BLACK(0, 0, 0);
	const Color4b Color4b::WHITE(255, 255, 255);
}