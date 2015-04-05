#pragma once
#include "uutIList.h"
#include <map>

namespace uut
{
	template<class TKey, class TValue>
	struct KeyValuePair
	{
		TKey key;
		TValue value;
	};

	template<class TKey, class TValue>
	class IDictionary : public IList<KeyValuePair<TKey,TValue>>
	{
	public:
		virtual void Add(const TKey& key, const TValue& value) = 0;
	};
}