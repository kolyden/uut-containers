#include "BufferLayout.h"

namespace uut
{
	BufferLayout::BufferLayout()
		: _layout(0)
	{
	}

	BufferLayout::~BufferLayout()
	{
		if (_layout)
			_layout->Release();
	}
}