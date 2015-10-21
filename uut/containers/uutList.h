#pragma once
#include "core/uutDefs.h"
#include <vector>
#include <functional>

namespace uut
{
	template<class T>
	class UUT_API List
	{
	public:
		typedef std::vector<T> Data;
		typedef typename Data::iterator Iterator;
		typedef typename Data::const_iterator ConstIterator;

		typedef std::function<bool(const T&)> Predicate;
		typedef std::function<int(const T&, const T&)> Comparer;

		List() {}
		List(const T* data, unsigned count) : _data(data, data + sizeof(data) / sizeof(T)) {}
		explicit List(int count) : _data(count) {}
		List(int count, const T& item) : _data(count, item) {}
		List(std::initializer_list<T> data) : _data(data) {}

		int Count() const { return (int)_data.size(); }
		T& GetAt(unsigned index) { return _data[index]; }
		const T& GetAt(unsigned index) const { return _data[index]; }

		T& operator[] (int index) { return _data[index]; }
		const T& operator[] (int index) const { return _data[index]; }

		bool IsEmpty() const { return _data.empty(); }

		void SetSize(unsigned int size) { _data.resize(size); }

		void Add(const T& item)
		{
			_data.push_back(item);
		}

		void Clear()
		{
			_data.clear();
		}

		bool Contains(const T& item) const
		{
			for (auto& it : _data)
			{
				if (it == item)
					return true;
			}

			return false;
		}

		template<class U> List<U> ConvertAll(std::function<U(const T&)> convert) const
		{
			const int count = Count();
			List<U> list(count);
			for (int i = 0; i < count; i++)
				list[i] = convert(_data[i]);
			return list;
		}

		bool Exist(Predicate predicate) const
		{
			for (auto& it : _data)
			{
				if (predicate(it))
					return true;
			}

			return false;
		}

		List<T> FindAll(Predicate predicate) const
		{
			List<T> list;
			for (auto& it : _data)
			{
				if (predicate(it))
					list << it;
			}

			return list;
		}

		int IndexOf(const T& item) const
		{
			const int count = Count();
			for (int i = 0; i < count; i++)
			{
				if (_data[i] == item)
					return i;
			}

			return -1;
		}

		List<T>& Insert(int index, const T& item)
		{
			_data.insert(_data.begin() + index, item);
			return *this;
		}

		int LastIndexOf(const T& item) const
		{
			const int count = Count();
			for (int i = count - 1; i >= 0; i--)
			{
				if (_data[i] == item)
					return i;
			}

			return -1;
		}

		bool Remove(const T& item)
		{
			for (auto it = Begin(); it != End(); ++it)
			{
				_data.erase(it);
				return true;
			}

			return false;
		}

		void Remove(Iterator iter)
		{
			_data.erase(iter);
		}

		int RemoveAll(Predicate predicate)
		{
			int count = 0;
			for (auto it = Begin(); it != End();)
			{
				if (predicate(*it))
				{
					_data.erase(it++);
					count++;
				}
				else ++it;
			}

			return count;
		}

		void RemoveAt(int index)
		{
			_data.erase(_data.begin() + index);
		}

		bool TrueForAll(Predicate predicate)
		{
			for (auto& it : _data)
			{
				if (!predicate(it))
					return false;
			}

			return true;
		}

		List& operator << (const T& item)
		{
			Add(item);
			return *this;
		}

		T* GetData() { return _data.data(); }
		const T* GetData() const { return _data.data(); }

		Iterator Begin() { return _data.begin(); }
		Iterator End() { return _data.end(); }
		ConstIterator Begin() const { return _data.begin(); }
		ConstIterator End() const { return _data.end(); }

		static const List EMPTY;

	protected:
		Data _data;
	};

	template<class T> const List<T> List<T>::EMPTY;

	template<class T> typename List<T>::Iterator begin(List<T>& list) { return list.Begin(); }
	template<class T> typename List<T>::Iterator end(List<T>& list) { return list.End(); }

	template<class T> typename List<T>::ConstIterator begin(const List<T>& list) { return list.Begin(); }
	template<class T> typename List<T>::ConstIterator end(const List<T>& list) { return list.End(); }
}