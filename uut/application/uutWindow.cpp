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
			_listeners[i]->OnMouseWheel(Vector2i::ZERO);

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
		int x, y, z;
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnKeyDown((EKeycode)wParam);
			break;

		case WM_KEYUP:
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnKeyUp((EKeycode)wParam);
			break;

		case WM_MOUSEMOVE:
			x = GET_X_LPARAM(lParam);
			y = GET_Y_LPARAM(lParam);
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseMove(Vector2i(x, y));

			{
				bool btnL = (wParam & MK_LBUTTON) != 0;
				bool btnR = (wParam & MK_RBUTTON) != 0;
				bool btnM = (wParam & MK_MBUTTON) != 0;

				/// LEFT BUTTON
				if (!window->_mouseButton[0] && btnL)
				{
					window->_mouseButton[0] = true;
					for (int i = 0; i < window->_listeners.Count(); i++)
						window->_listeners[i]->OnMouseDown(0);
				}

				if (window->_mouseButton[0] && !btnL)
				{
					window->_mouseButton[0] = false;
					for (int i = 0; i < window->_listeners.Count(); i++)
						window->_listeners[i]->OnMouseUp(0);
				}

				// RIGHT BUTTON
				if (!window->_mouseButton[1] && btnR)
				{
					window->_mouseButton[1] = true;
					for (int i = 0; i < window->_listeners.Count(); i++)
						window->_listeners[i]->OnMouseDown(1);
				}

				if (window->_mouseButton[1] && !btnR)
				{
					window->_mouseButton[1] = false;
					for (int i = 0; i < window->_listeners.Count(); i++)
						window->_listeners[i]->OnMouseUp(1);
				}
			}
			break;

		case WM_MOUSEWHEEL:
			z = GET_WHEEL_DELTA_WPARAM(wParam);
			for (int i = 0; i < window->_listeners.Count(); i++)
				window->_listeners[i]->OnMouseWheel(Vector2i(0, z));
			break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}