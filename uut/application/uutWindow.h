#pragma once
#include "core/uutModule.h"
#include "core/uutPtr.h"
#include "containers/uutList.h"
#include "math/uutVector2.h"
#include <bitset>

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

		void SetTitle(const String& title);
		const Vector2i& GetSize() const { return _size; }

		void AddEventListener(EventListener* listener);
		void RemoveEventListener(EventListener* listener);

		HWND GetHWND() const { return _hwnd; }

	protected:
		HWND _hwnd;
		WNDCLASSEX _wc;
		Vector2i _size;
		List<EventListener*> _listeners;
		std::bitset<3> _mouseButton;

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}