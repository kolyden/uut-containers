#pragma once
#include "core/Defs.h"
#include <map>

namespace uut
{
	template<class TKey, class TValue>
	class UUT_API Dictionary
	{
	public:
		void Add(const TKey& key, const TValue>& val)
		{
			_data.insert(std::pair<TKey, TValue>(key, val));
		}

		void Clear()
		{
			_data.clear();
		}

		int Count() const { return (int)_data.size(); }

		bool Contains(const TKey& key) const
		{
			auto it = _data.find(key);
			return it != _data.end();
		}

		bool TryGet(const TKey& key, TValue* val)
		{
			auto it = _data.find(key);
			if (it == _data.end())
				return false;

			*val = it->second;
			return true;
		}

	protected:
		std::vector<TKey, TValue> _data;
	};
}