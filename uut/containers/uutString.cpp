#include "uutString.h"

namespace uut
{
	const String String::EMPTY;

	String::String()
	{
	}

	String::String(const char* str)
		: _data(str)
	{
	}

	String::String(String&& str)
		: _data(std::move(str._data))
	{
	}

	void String::Clear()
	{
		_data.clear();
	}
}