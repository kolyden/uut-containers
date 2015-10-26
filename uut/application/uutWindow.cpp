#include "uutWindow.h"
#include "input/uutInput.h"
#include "application/uutEventListener.h"
#include <windows.h>
#include <windowsx.h>

namespace uut
{
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Window::Window()
		: _handle(0)
		, _size(0, 0)
	{
	}

	bool Window::Create(const Vector2i& size)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		_size = size;

		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = &WindowProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = "UUTEngineWindow";

		// register the window class
		RegisterClassEx(&wc);

// 		RECT wr = { 0, 0, _size.x, _size.y };    // set the size, but not the position
// 		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

		// create the window and use the result as the handle
		_handle = CreateWindowEx(NULL,
			wc.lpszClassName,    // name of the window class
			"Engine Window",   // title of the window
			WS_OVERLAPPEDWINDOW,    // window style
			0,    // x-position of the window
			0,    // y-position of the window
			size.x,    // width of the window
			size.y,    // height of the window
			NULL,    // we have no parent window, NULL
			NULL,    // we aren't using menus, NULL
			hInstance,    // application handle
			NULL);    // used with multiple windows, NULL

		SetWindowLongPtr((HWND)_handle, GWL_USERDATA, (LONG_PTR)this);
		ShowWindow((HWND)_handle, SW_SHOW);

		return true;
	}

	bool Window::MessagePool()
	{
		MSG msg;

		for (int i = 0; i < _listeners.Count(); i++)
			_listeners[i]->OnMouseWheel(0);

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);

			// check to see if it's time to quit
			if (msg.message == WM_QUIT)
				return false;
		}

		return true;
	}

	void Window::SetTitle(const String& title)
	{
		SetWindowTextA((HWND)_handle, title);
	}

	void Window::AddEventListener(EventListener* listener)
	{
		if (listener == nullptr)
			return;

		_listeners << listener;
	}

	void Window::RemoveEventListener(EventListener* listener)
	{
		if (listener == nullptr)
			return;

		for (auto it = _listeners.Begin(); it != _listeners.End(); ++it)
		{
			if (*it != listener)
				continue;

			_listeners.Remove(it);
			return;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		auto win = (Window*)GetWindowLongPtr(hWnd, GWL_USERDATA);
		int x, y;
		float wheel;

		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			if (wParam < 256)
			{
				for (auto& it : win->GetListeners())
					it->OnKeyDown((EKeycode)wParam);
				return true;
			}
			break;

		case WM_KEYUP:
			if (wParam < 256)
			{
				for (auto& it : win->GetListeners())
					it->OnKeyUp((EKeycode)wParam);
				return true;
			}
			break;

		case WM_LBUTTONDOWN:
			for (auto& it : win->GetListeners())
				it->OnMouseDown(0);
			return true;

		case WM_LBUTTONUP:
			for (auto& it : win->GetListeners())
				it->OnMouseUp(0);
			return true;

		case WM_RBUTTONDOWN:
			for (auto& it : win->GetListeners())
				it->OnMouseDown(1);
			return true;

		case WM_RBUTTONUP:
			for (auto& it : win->GetListeners())
				it->OnMouseUp(1);
			return true;

		case WM_MBUTTONDOWN:
			for (auto& it : win->GetListeners())
				it->OnMouseDown(2);
			return true;

		case WM_MBUTTONUP:
			for (auto& it : win->GetListeners())
				it->OnMouseUp(2);
			return true;

		case WM_MOUSEMOVE:
			x = GET_X_LPARAM(lParam);
			y = GET_Y_LPARAM(lParam);
			for (auto& it : win->GetListeners())
				it->OnMouseMove(Vector2i(x, y));
			return true;

		case WM_MOUSEWHEEL:
			wheel = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / 120.0f;
			for (auto& it : win->GetListeners())
				it->OnMouseWheel(wheel);
			return true;

		case WM_CHAR:
			// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
			if (wParam > 0 && wParam < 0x10000)
			{
				for (auto& it : win->GetListeners())
					it->OnChar(wParam);
				return true;
			}
			break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}