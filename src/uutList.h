#pragma once
#include "uutIList.h"
#include <vector>

namespace uut
{
	template<class T>
	class List : public IList<T>
	{
	public:
		virtual void Add(const T& item) override { _data.push_back(item); }
		virtual void Clear() override { _data.clear(); }

		virtual int Count() const override { return (int)_data.size(); }
		virtual T& GetAt(unsigned index) override { return _data[index]; }
		virtual const T& GetAt(unsigned index) const override { return _data[index]; }

	protected:
		std::vector<T> _data;
	};
}