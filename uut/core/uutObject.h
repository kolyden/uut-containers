#pragma once
#include "uutPtr.h"

namespace uut
{
	class Context;
	class Module;

	class UUT_API Object : public RefCounted
	{
	public:
		virtual ~Object() {}
	};
}