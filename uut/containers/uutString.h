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
		String(String&& str);

		operator const char* ()  const { return _data.c_str(); }

		static const String EMPTY;

	protected:
		std::string _data;
	};
}