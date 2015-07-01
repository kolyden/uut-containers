#pragma once
#include "core/uutDefs.h"

namespace uut
{
	namespace Math
	{
		static const float M_PI = 3.14159265358979323846264338327950288f;
		static const float M_HALF_PI = M_PI * 0.5f;
		static const float M_EPSILON = 0.000001f;
		static const float M_DEGTORAD = (float)M_PI / 180.0f;
		static const float M_RADTODEG = 1.0f / M_DEGTORAD;

		extern float Deg2Rad(float deg);
		extern float Rad2Deg(float rad);
	}
}