#pragma once
#include "core/uutModule.h"
#include "core/uutPtr.h"
#include "containers/uutList.h"

namespace uut
{
	class EventListener;

	class Window : public Module
	{
		OBJECT(Window, Module)
	public:
		Window();

		bool Create(int width, int height);
		bool MessagePool();

		void AddEventListener(EventListener* listener);
		void RemoveEventListener(EventListener* listener);

		HWND GetHWND() const { return _hwnd; }

	protected:
		HWND _hwnd;
		WNDCLASSEX _wc;
		List<EventListener*> _listeners;

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}