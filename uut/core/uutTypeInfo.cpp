#include "uutTypeInfo.h"

namespace uut
{
	const TypeInfo TypeInfo::EMPTY;

	TypeInfo::TypeInfo() : _index(typeid(nullptr)) {}

	TypeInfo::TypeInfo(const char* name, std::type_index index)
		: _name(name)
		, _index(index)
	{
	}
}