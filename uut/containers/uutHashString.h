#pragma once
#include "uutString.h"

namespace uut
{
	class HashString
	{
	public:
		HashString();
		HashString(const char* str);
		HashString(const HashString& str);
		HashString(HashString&& str);

		const char*	GetData() const { return _data.c_str(); }
		int GetHash() const { return _hash; }

		operator int() const { return _hash; }
		bool IsEmpty() const { return (_hash == 0); }

		HashString& operator = (const HashString& str);
		HashString& operator = (HashString&& str);

		bool operator == (const HashString& str) const { return _hash == str._hash; }
		bool operator != (const HashString& str) const { return _hash == str._hash; }
		bool operator <= (const HashString& str) const { return _hash <= str._hash; }
		bool operator >= (const HashString& str) const { return _hash >= str._hash; }
		bool operator < (const HashString& str) const { return _hash < str._hash; }
		bool operator > (const HashString& str) const { return _hash > str._hash; }

		static const HashString EMPTY;

	protected:
		std::string _data;
		int _hash;

		int CalcHash() const;
	};
}