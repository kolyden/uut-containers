#include "uutWindow.h"
#include "core/uutCore.h"
#include "input/uutInput.h"

namespace uut
{
	Window::Window()
		: _hwnd(0)
		, _wc({ 0 })
		, _input(new Input())
	{
		GetCore()->AddModule(_input);
	}

	bool Window::Create(int width, int height)
	{
		HINSTANCE hinstance = GetModuleHandle(NULL);

		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = &WindowProc;
		wc.hInstance = hinstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = "UUTEngineWindow";

		// register the window class
		RegisterClassEx(&wc);

		RECT wr = { 0, 0, width, height };    // set the size, but not the position
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

		// create the window and use the result as the handle
		_hwnd = CreateWindowEx(NULL,
			wc.lpszClassName,    // name of the window class
			"Engine Window",   // title of the window
			WS_OVERLAPPEDWINDOW,    // window style
			300,    // x-position of the window
			300,    // y-position of the window
			wr.right - wr.left,    // width of the window
			wr.bottom - wr.top,    // height of the window
			NULL,    // we have no parent window, NULL
			NULL,    // we aren't using menus, NULL
			hinstance,    // application handle
			NULL);    // used with multiple windows, NULL

		SetWindowLongPtr(_hwnd, GWL_USERDATA, (LONG_PTR)this);
		ShowWindow(_hwnd, SW_SHOW);

		return true;
	}

	Input* Window::GetInput() const
	{
		return _input;
	}

	LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		auto window = (Window*)GetWindowLongPtr(hWnd, GWL_USERDATA);
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			window->_input->_keys[wParam] = true;
			break;

		case WM_KEYUP:
			window->_input->_keys[wParam] = false;
			break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}