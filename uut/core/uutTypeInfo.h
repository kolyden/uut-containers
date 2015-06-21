#pragma once
#include "containers/uutHashString.h"
#include <typeinfo>
#include <typeindex>

namespace uut
{
	struct TypeInfo
	{
		HashString _name;
		std::type_index _index;

		TypeInfo();
		TypeInfo(const char* name, std::type_index index);

		static const TypeInfo EMPTY;
	};
}