#pragma once
#include "core/uutDefs.h"
#include "uutList.h"
#include <string>

namespace uut
{
	class String
	{
	public:
		typedef std::string Data;
		typedef Data::iterator Iterator;
		typedef Data::const_iterator ConstIterator;

		String();
		String(const char* str);
		String(const String& str);
		String(String&& str);
		String(const List<char>& list);

		int Length() const { return (int)_data.size(); }

		char& operator[] (int index) { return _data[index]; }
		char operator[] (int index) const { return _data[index]; }

		bool EndsWith(const String& value) const;
		bool Equals(const String& str) const;
		bool Equals(const String& str, bool ignoreCase) const;

		int IndexOf(char c) const;

		String& Insert(int index, char c);

		void Clear();

		operator const char* ()  const { return _data.c_str(); }

		String& operator = (const String& str);
		String& operator = (String&& str);

		Iterator Begin() { return _data.begin(); }
		Iterator End() { return _data.end(); }
		ConstIterator Begin() const { return _data.begin(); }
		ConstIterator End() const { return _data.end(); }

		static const String EMPTY;

	protected:
		Data _data;
	};
 
	extern String::Iterator begin(String& str);
	extern String::Iterator end(String& str);

	extern String::ConstIterator begin(const String& str);
	extern String::ConstIterator end(const String& str);
}