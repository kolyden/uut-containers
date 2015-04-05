#pragma once

namespace uut
{
	template<class T>
	class ICollection
	{
	public:
		virtual int Count() const = 0;
		virtual T& GetAt(unsigned index) = 0;
		virtual const T& GetAt(unsigned index) const = 0;

		virtual bool Contains(const T& item) const
		{
			return IndexOf(item) >= 0;
		}

		virtual int IndexOf(const & item) const
		{
			for (int i = 0; i < Count(); i++)
			{
				if (GetAt(i) == item)
					return i;
			}

			return -1;
		}
	};
}