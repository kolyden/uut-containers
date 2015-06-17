#include "BufferLayout.h"

namespace uut
{
	BufferLayout::BufferLayout(Video* video)
		: VideoObject(video)
		, _layout(0)
	{
	}

	BufferLayout::~BufferLayout()
	{
		if (_layout)
			_layout->Release();
	}
}