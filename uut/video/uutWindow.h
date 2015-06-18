#pragma once
#include "core/uutDefs.h"

namespace uut
{
	class Window
	{
	public:
		Window();

		bool Create(int width, int height);

		HWND GetHWND() const { return _hwnd; }

	protected:
		HWND _hwnd;
		WNDCLASSEX _wc;

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}