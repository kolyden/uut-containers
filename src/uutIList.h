#pragma once
#include "uutICollection.h"

namespace uut
{
	template<class T>
	class IList : public ICollection<T>
	{
	public:
		virtual void Add(const T& item) = 0;
		virtual void Clear() = 0;
	};
}