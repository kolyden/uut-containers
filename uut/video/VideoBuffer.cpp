#include "VideoBuffer.h"

namespace uut
{
	VideoBuffer::VideoBuffer()
		: _data(nullptr)
	{
	}

	VideoBuffer::~VideoBuffer()
	{
		if (_data)
			_data->Release();
	}

}