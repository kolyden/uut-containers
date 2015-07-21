#pragma once
#include "core/uutPtr.h"
#include "input/uutKeycodes.h"
#include "math/uutVector2.h"

namespace uut
{
	class EventListener
	{
	public:
		virtual void OnKeyDown(EKeycode code) {}
		virtual void OnKeyUp(EKeycode code) {}

		virtual void OnMouseDown(int button) {}
		virtual void OnMouseUp(int button) {}
		virtual void OnMouseMove(const Vector2i& pos) {}
		virtual void OnMouseWheel(float delta) {}
	};
}