#pragma once
#include "core/uutModule.h"
#include "core/uutPtr.h"
#include "containers/uutList.h"
#include "math/uutVector2.h"

namespace uut
{
	class EventListener;

	class Window : public Module
	{
		OBJECT(Window, Module)
	public:
		Window();

		bool Create(const Vector2i& size);
		bool MessagePool();

		const Vector2i& GetSize() const { return _size; }

		void AddEventListener(EventListener* listener);
		void RemoveEventListener(EventListener* listener);

		HWND GetHWND() const { return _hwnd; }

	protected:
		HWND _hwnd;
		WNDCLASSEX _wc;
		Vector2i _size;
		List<EventListener*> _listeners;

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}