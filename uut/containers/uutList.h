#pragma once
#include "core/uutDefs.h"
#include <vector>

namespace uut
{
	template<class T>
	class UUT_API List
	{
	public:
		List() {}
		List(const T* data, unsigned count) : _data(data, data + sizeof(data) / sizeof(T)) {}
		List(std::initializer_list<T> data) : _data(data) {}

		void Add(const T& item) { _data.push_back(item); }
		void Clear() { _data.clear(); }

		void SetSize(unsigned int size) { _data.resize(size); }

		int Count() const { return (int)_data.size(); }
		T& GetAt(unsigned index) { return _data[index]; }
		const T& GetAt(unsigned index) const { return _data[index]; }

		T& operator[] (int index) { return _data[index]; }
		const T& operator[] (int index) const { return _data[index]; }

		T* GetData() { return _data.data(); }
		const T* GetData() const { return _data.data(); }

	protected:
		std::vector<T> _data;
	};
}