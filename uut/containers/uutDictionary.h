#pragma once
#include "core/uutDefs.h"
#include <map>

namespace uut
{
	template<class TKey, class TValue>
	class UUT_API Dictionary
	{
	public:
		typedef std::map<TKey, TValue> Data;
		typedef typename Data::iterator Iterator;
		typedef typename Data::const_iterator ConstIterator;

		Dictionary() {}
		Dictionary(Dictionary<TKey, TValue>&& other) { _data = std::move(other._data); }
		Dictionary(std::initializer_list<std::pair<TKey, TValue>> items)
			: _data(items) {}

		void Add(const TKey& key, const TValue& val)
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

		Iterator Find(const TKey& key)
		{
			return _data.find(key);
		}

		ConstIterator Find(const TKey& key) const
		{
			return _data.find(key);
		}

		TValue& operator[] (const TKey& key)
		{
			return _data[key];
		}

		const TValue& operator[] (const TKey& key) const
		{
			return _data[key];
		}

		Dictionary<TKey, TValue>& operator=(Dictionary<TKey, TValue>&& other)
		{
			if (this != other)
				_dataMap = std::move(other._data);
			return *this;
		}

		Iterator Begin() { return _data.begin(); }
		Iterator End() { return _data.end(); }
		ConstIterator Begin() const { return _data.begin(); }
		ConstIterator End() const { return _data.end(); }

		static const Dictionary EMPTY;

	protected:
		Data _data;
	};

	template<class TKey, class TValue>
	const Dictionary<TKey, TValue> Dictionary<TKey, TValue>::EMPTY;

	template<class TKey, class TValue> typename Dictionary<TKey, TValue>::Iterator begin(Dictionary<TKey, TValue>& list) { return list.Begin(); }
	template<class TKey, class TValue> typename Dictionary<TKey, TValue>::Iterator end(Dictionary<TKey, TValue>& list) { return list.End(); }

	template<class TKey, class TValue> typename Dictionary<TKey, TValue>::ConstIterator begin(const Dictionary<TKey, TValue>& list) { return list.Begin(); }
	template<class TKey, class TValue> typename Dictionary<TKey, TValue>::ConstIterator end(const Dictionary<TKey, TValue>& list) { return list.End(); }
}