#pragma once
#include "core/uutDefs.h"
#include <string>

namespace uut
{
	class String
	{
	public:
		String();
		String(const char* str);
		String(const String& str);
		String(String&& str);

		void Clear();

		operator const char* ()  const { return _data.c_str(); }

		String& operator = (const String& str);
		String& operator = (String&& str);

		static const String EMPTY;

	protected:
		std::string _data;
	};
}