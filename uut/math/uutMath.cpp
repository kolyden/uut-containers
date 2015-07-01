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

}