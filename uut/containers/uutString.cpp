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

	String::String(const String& str)
		: _data(str._data)
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

	String& String::operator=(const String& str)
	{
		_data = str._data;
		return *this;
	}

	String& String::operator=(String&& str)
	{
		_data = std::move(str._data);
		return *this;
	}
}