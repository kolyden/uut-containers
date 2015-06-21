#include "uutInput.h"
#include "application/uutWindow.h"

namespace uut
{
	Input::Input()
	{
		_keys.reset();
	}

	//////////////////////////////////////////////////////////////////////////
	void Input::OnInit()
	{
		_window = GetModule<Window>();
		_window->AddEventListener(this);
	}

	void Input::OnDone()
	{
		_window->RemoveEventListener(this);
	}

	void Input::OnKeyDown(EKeycode code)
	{
		_keys[code] = true;
	}

	void Input::OnKeyUp(EKeycode code)
	{
		_keys[code] = false;
	}
}