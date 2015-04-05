#pragma once
#include "uutICollection.h"

namespace game
{
	template<class T, int numElements>
	class Array : public ICollection<T>
	{
	public:
		virtual unsigned Count() const override { return numElements; }
		virtual T& GetAt(unsigned index) override { return _data[index]; }
		virtual const T& GetAt(unsigned index) const override { return _data[index]; }

		void Zero() { memset(_data, 0, sizeof(_data)); }
		T* GetData() { return _data; }
		const T* GetData() const { return _data; }

	protected:
		T _data[numElements];
	};
}