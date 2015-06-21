#include "uutHashString.h"

namespace uut
{
	const HashString HashString::EMPTY;

	HashString::HashString()
		: _hash(0)
	{
	}

	HashString::HashString(const char* str)
		: _data(str)
		, _hash(CalcHash())
	{
	}

	HashString::HashString(HashString&& str)
		: _data(std::move(str._data))
		, _hash(std::move(str._hash))
	{
	}

	int HashString::CalcHash() const
	{
		static std::hash<std::string> hash_fn;
		return hash_fn(_data);
	}
}