#pragma one
#include "uutIDictionary.h"

namespace uut
{
	template<class TKey, class TValue>
	class Dictionary : public IDictionary
	{
	public:
		virtual void Add(const KeyValuePair<TKey, TValue>& item) override
		{
			_data.insert(item);
		}

		virtual void Clear() override
		{
			_data.clear();
		}

		virtual int Count() const override { return (int)_data.size(); }
		virtual KeyValuePair<TKey, TValue>& GetAt(unsigned index) override { return _data[index]; }
		virtual const KeyValuePair<TKey, TValue>& GetAt(unsigned index) const override { return _data[index]; }

	protected:
		std::vector<KeyValuePair<TKey, TValue>> _data;
	};
}