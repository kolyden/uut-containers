#pragma once
#include "Ptr.h"

namespace uut
{
	class Object : public RefCounted
	{
	public:
		virtual ~Object() {}
	};
}