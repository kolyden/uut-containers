#include "uutRandom.h"

namespace uut
{
	float Random::Value()
	{
		return static_cast<float>(rand()) / RAND_MAX;
	}
}