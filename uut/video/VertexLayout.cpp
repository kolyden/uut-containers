#include "VertexLayout.h"

namespace uut
{
	VertexLayout::VertexLayout(Video* video)
		: VideoObject(video)
		, _layout(0)
	{
	}

	VertexLayout::~VertexLayout()
	{
		if (_layout)
			_layout->Release();
	}
}