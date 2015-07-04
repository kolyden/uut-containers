#include "uutVertexLayout.h"

namespace uut
{
	VertexLayout::VertexLayout()
		: _data(0)
	{
	}

	VertexLayout::~VertexLayout()
	{
		if (_data)
			_data->Release();
	}
}