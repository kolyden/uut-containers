#pragma once
#include "core/uutModule.h"
#include "containers/uutDictionary.h"
#include "application/uutEventListener.h"
#include <bitset>

namespace uut
{
	class Window;

	class Input : public Module, public EventListener
	{
		OBJECT(Input, Module)
	public:
		Input();

		bool IsKey(EKeycode key) const { return _keys[key]; }

	protected:
		WeakPtr<Window> _window;
		static const int KEYS_COUNT = 256;
		std::bitset<KEYS_COUNT> _keys;

		virtual void OnInit() override;
		virtual void OnDone() override;

		virtual void OnKeyDown(EKeycode code) override;
		virtual void OnKeyUp(EKeycode code) override;

		friend class Window;
	};
}