#pragma once
#include "uutPtr.h"

namespace uut
{
	class Object : public RefCounted
	{
	public:
		virtual ~Object() {}
	};
}