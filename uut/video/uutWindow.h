#pragma once
#include "core/uutObject.h"
#include "core/uutPtr.h"

namespace uut
{
	class Input;

	class Window : public Object
	{
	public:
		Window();

		bool Create(int width, int height);

		HWND GetHWND() const { return _hwnd; }

		Input* GetInput() const;

	protected:
		HWND _hwnd;
		WNDCLASSEX _wc;
		SharedPtr<Input> _input;

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}