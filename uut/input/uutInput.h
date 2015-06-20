#pragma once
#include "core/uutObject.h"
#include "containers/uutDictionary.h"
#include "uutKeycodes.h"
#include <bitset>

namespace uut
{
	class Input : public Object
	{
	public:
		Input();

		bool IsKey(EKeycode key) const { return _keys[key]; }

	protected:
		static const int KEYS_COUNT = 256;
		std::bitset<KEYS_COUNT> _keys;

		friend class Window;
	};
}