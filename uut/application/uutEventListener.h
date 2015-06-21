#pragma once
#include "core/uutPtr.h"
#include "input/uutKeycodes.h"

namespace uut
{
	class EventListener
	{
	public:
		virtual void OnKeyDown(EKeycode code) {}
		virtual void OnKeyUp(EKeycode code) {}
	};
}