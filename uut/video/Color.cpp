#include "Color.h"

namespace uut
{
	const Color Color::BLACK(0, 0, 0);
	const Color Color::WHITE(1, 1, 1);

	Color::Color() {}

	Color::Color(float _r, float _g, float _b)
		: r(_r), g(_g), b(_b), a(1.0f)
	{
	}

	Color::Color(float _r, float _g, float _b, float _a)
		: r(_r), g(_g), b(_b), a(_a)
	{
	}
}