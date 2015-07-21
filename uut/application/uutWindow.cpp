#include "uutWindow.h"
#include "core/uutCore.h"
#include "input/uutInput.h"
#include "application/uutEventListener.h"

namespace uut
{
	Window::Window()
		: _hwnd(0)
		, _wc({ 0 })
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
		_hwnd = CreateWindowEx(NULL,
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

		SetWindowLongPtr(_hwnd, GWL_USERDATA, (LONG_PTR)this);
		ShowWindow(_hwnd, SW_SHOW);

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
		SetWindowTextA(_hwnd, title);
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
	LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		auto window = (Window*)GetWindowLongPtr(hWnd, GWL_USERDATA);
		int x, y;
		float wheel;

		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnKeyDown((EKeycode)wParam);
			return 0;
			break;

		case WM_KEYUP:
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnKeyUp((EKeycode)wParam);
			return 0;
			break;

		case WM_LBUTTONDOWN:
			window->_mouseButton[0] = true;
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseDown(0);
			return 0;
			break;

		case WM_LBUTTONUP:
			window->_mouseButton[0] = false;
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseUp(0);
			return 0;
			break;

		case WM_RBUTTONDOWN:
			window->_mouseButton[1] = true;
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseDown(1);
			return 0;
			break;

		case WM_RBUTTONUP:
			window->_mouseButton[1] = false;
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseUp(1);
			return 0;
			break;

		case WM_MBUTTONDOWN:
			window->_mouseButton[2] = true;
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseDown(2);
			return 0;
			break;

		case WM_MBUTTONUP:
			window->_mouseButton[2] = false;
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseUp(2);
			return 0;
			break;

		case WM_MOUSEMOVE:
			x = GET_X_LPARAM(lParam);
			y = GET_Y_LPARAM(lParam);
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseMove(Vector2i(x, y));
			return 0;
			break;

		case WM_MOUSEWHEEL:
			wheel = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / 120.0f;
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseWheel(wheel);
			return 0;
			break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}