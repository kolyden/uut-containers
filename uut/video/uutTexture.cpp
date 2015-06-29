#include "uutTexture.h"

namespace uut
{
	Texture::Texture()
		: _data(NULL)
		, _size(0)
	{
	}

	Texture::~Texture()
	{
		if (_data != nullptr)
			_data->Release();
	}
}