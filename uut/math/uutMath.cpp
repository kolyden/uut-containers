#include "uutMath.h"

namespace uut
{
	extern float Math::Deg2Rad(float deg)
	{
		return deg * M_DEGTORAD;
	}

	extern float Math::Rad2Deg(float rad)
	{
		return rad * M_RADTODEG;
	}

	extern bool Math::Equals(float lhs, float rhs)
	{
		return lhs + M_EPSILON >= rhs && lhs - M_EPSILON <= rhs;
	}

	float Math::Floor(float val) { return ::floorf(val); }
	float Math::Ceil(float val) { return ::ceilf(val); }
	float Math::Round(float val) { return ::roundf(val); }

	int Math::FloorToInt(float val)
	{
		return static_cast<int>(Floor(val));
	}

	int Math::CeilToInt(float val)
	{
		return static_cast<int>(Ceil(val));
	}

	int Math::RoundToInt(float val)
	{
		return static_cast<int>(Round(val));
	}
}