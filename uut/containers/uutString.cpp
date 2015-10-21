#include "uutString.h"
#include <locale>

namespace uut
{
	static bool icompare_pred(unsigned char a, unsigned char b)
	{
		return true;
// 		static std::locale loc;
// 		return std::tolower(a, loc) == std::tolower(b, loc);
	}

	//////////////////////////////////////////////////////////////////////////
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

	String::String(const List<char>& list)
		: _data(list.Begin(), list.End())
	{
	}

	bool String::EndsWith(const String& value) const
	{
		return _data.size() >= value._data.size() &&
			_data.compare(_data.size() - value._data.size(), value._data.size(), value._data) == 0;
	}

	bool String::Equals(const String& str) const
	{
		return _data.compare(str) == 0;
	}

	bool String::Equals(const String& str, bool ignoreCase) const
	{
		if (ignoreCase)
		{
			return std::lexicographical_compare(_data.begin(), _data.end(),
				str._data.begin(), str._data.end(), icompare_pred);
		}
		else return _data.compare(str) == 0;
	}

	int String::IndexOf(char c) const
	{
		const int count = Length();
		for (int i = 0; i < count; i++)
		{
			if (_data[i] == c)
				return i;
		}

		return -1;
	}

	String& String::Insert(int index, char c)
	{
		_data.insert(_data.begin() + index, c);
		return *this;
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

	//////////////////////////////////////////////////////////////////////////
	extern String::Iterator begin(String& str)
	{
		return str.Begin();
	}

	extern String::ConstIterator begin(const String& str)
	{
		return str.Begin();
	}

	extern String::Iterator end(String& str)
	{
		return str.End();
	}

	extern String::ConstIterator end(const String& str)
	{
		return str.End();
	}
}